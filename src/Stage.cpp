#include "Stage.h"

Stage::Stage(void) {
	m_frame = 0;
	m_fps = 0;
	m_timer = 0;
	m_lastSecond = 0;
	m_forwardRendering = true;
	m_terminated = false;
	m_bgColor = glm::vec3(0, 0, 0);
	m_camera = 0;
}

Stage::~Stage(void) {

}

void Stage::init(int width, int height, int framerate, int fsaa, bool fullscreen) {
	m_width = width;
	m_height = height;
	m_framerate = framerate;

	int windowMode = GLFW_WINDOW;
	if (fullscreen) windowMode = GLFW_FULLSCREEN;

	if (!glfwInit()) {
		std::cerr << "glfwInit failed" << std::endl;
		exit(1);
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, fsaa);
	if (!glfwOpenWindow(m_width, m_height, 0, 0, 0, 0, 32, 0, windowMode)) {
		std::cerr << "glfwOpenWindow failed" << std::endl;
		glfwTerminate();
		exit(1);
	}

	if (GLenum err = glewInit() != GLEW_OK) {
		std::cerr << "glewInit failed: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		exit(1);
	}

	m_allShaders.init();
	
	glClearColor(0, 0, 0, 0);
}

void Stage::dispose(void) {
	if (m_terminated == false) {
		for (unsigned int i = 0; i < m_meshes.size();) {
			m_meshes[i]->geometry->deleteBuffers();
			m_meshes[i]->material->deleteBuffers();
			m_meshes.erase(m_meshes.begin() + i);
		}
		for (unsigned int i = 0; i < m_lights.size();) {
			m_lights.erase(m_lights.begin() + i);
		}
		glfwTerminate();
		m_terminated = true;
	}
}

void Stage::run(void) {
	initGL();
	initShadowMaps();

	m_lastTime = glfwGetTime();
	m_running = true;
	while (m_running) {
		double currentTime = glfwGetTime();
		// limit fps
		if (m_framerate == 0 || currentTime - m_timer > 1.0f / float(m_framerate)) {
			update(currentTime);
			if (m_camera != 0) render();
		}
	}
}

void Stage::update(double currentTime) {
	m_timer = currentTime;
	calculateFps(currentTime);

	//check if glfw window has been closed
	if (!glfwGetWindowParam(GLFW_OPENED)) {
		m_running = false;
	}

	//callback and give delta (time between frames) in seconds
	updateCallback(float(currentTime - m_lastTime));
	m_lastTime = currentTime;
	m_frame++;
}

void Stage::render(void) {
	clearScreen();
	if (m_forwardRendering) {
		forwardRender();
	}
	glfwSwapBuffers();
}

void Stage::forwardRender(void) {
	initForwardRendering();
	renderDepth();

	//in forward rendering the scene is rendered for each light and blended together
	for (unsigned int i = 0; i < m_lights.size(); ++i) {
		initLightRendering();

		Camera shadowMapCamera;
		BaseShadowMap* baseShadowMap = 0;
		ShaderProgram* finalShader = 0;
		if (m_lights[i]->getType() == LightTypes::PointLight) {
			if (m_lights[i]->shadow != Shadows::None) baseShadowMap = &m_shadowCubeMap;
			renderPointLightShadowMap(m_lights[i], &shadowMapCamera);
			finalShader = getCorrectPointLightShadowShader(m_lights[i]);
		} else if (m_lights[i]->getType() == LightTypes::DirectionalLight) {
			if (m_lights[i]->shadow != Shadows::None) baseShadowMap = &m_shadowMap;
			renderDirectionalLightShadowMap(m_lights[i], &shadowMapCamera);
			finalShader = getCorrectDirectionalLightShadowShader(m_lights[i]);
		}
		renderColor(m_lights[i], i, finalShader, &shadowMapCamera, baseShadowMap);
	}
}

void Stage::initGL(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void Stage::initShadowMaps(void) {
	m_shadowMap.init(2048, 2048); //setup framebuffer and texture for directional light shadow map
	m_shadowCubeMap.init(512, 512); //same for point light shadow cube map
}

void Stage::calculateFps(double currentTime) {
	if (currentTime - m_lastSecond > 1.0f) {
		m_lastSecond = currentTime;
		m_fps = m_frame;
		m_frame = 0;
		std::cout << m_fps << std::endl;
	}
}

void Stage::initForwardRendering(void) {
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
}

void Stage::initLightRendering(void) {
	glDisable(GL_BLEND);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
}

void Stage::renderDepth(void) {
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	renderScene(&m_allShaders.noLight, m_camera);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void Stage::renderColor(Light* light, int lightIndex, ShaderProgram* colorShader, Camera* shadowMapCamera, BaseShadowMap* baseShadowMap) {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//if not the first light rendered then tell opengl to blend colors
	if (lightIndex > 0) {
		glEnable(GL_BLEND);
	} else {
		glDisable(GL_BLEND);
	}
	glDepthFunc(GL_EQUAL);
					
	glViewport(0, 0, m_width, m_height);

	glDepthMask(GL_FALSE);
	renderScene(colorShader, m_camera, 0, light, shadowMapCamera, baseShadowMap);
	glDepthMask(GL_TRUE);
}

void Stage::renderPointLightShadowMap(Light* light, Camera* shadowMapCamera) {
	if (light->shadow != Shadows::None) {
		//if point light render to a shadow cube map
		//each cube face contains lights vision of the direction
		shadowMapCamera->initPerspective(90, 1, 0.1f, 100);
		glm::vec3 lightPosition = light->getPosition();

		m_shadowCubeMap.bind();
		//render x direction
		m_shadowCubeMap.attach(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowMapCamera->lookAt(lightPosition, lightPosition + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0));
		renderScene(&m_allShaders.omniDepth, shadowMapCamera, light);

		//render -x direction
		m_shadowCubeMap.attach(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowMapCamera->lookAt(lightPosition, lightPosition + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0));
		renderScene(&m_allShaders.omniDepth, shadowMapCamera, light);

		//render y direction
		m_shadowCubeMap.attach(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowMapCamera->lookAt(lightPosition, lightPosition + glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
		renderScene(&m_allShaders.omniDepth, shadowMapCamera, light);

		//render -y direction
		m_shadowCubeMap.attach(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowMapCamera->lookAt(lightPosition, lightPosition + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1));
		renderScene(&m_allShaders.omniDepth, shadowMapCamera, light);

		//render z direction
		m_shadowCubeMap.attach(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowMapCamera->lookAt(lightPosition, lightPosition + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));
		renderScene(&m_allShaders.omniDepth, shadowMapCamera, light);

		//render -z direction
		m_shadowCubeMap.attach(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowMapCamera->lookAt(lightPosition, lightPosition + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));
		renderScene(&m_allShaders.omniDepth, shadowMapCamera, light);

		m_shadowCubeMap.unbind();
	}
}

ShaderProgram* Stage::getCorrectPointLightShadowShader(Light* light) {			
	if (light->shadow == Shadows::Basic) {
		return &m_allShaders.omniBasic;
	} else if (light->shadow == Shadows::PCF) {
		return &m_allShaders.omniPcf;
	}
	return &m_allShaders.omniNoShadow;
}

void Stage::renderDirectionalLightShadowMap(Light* light, Camera* shadowMapCamera) {
	if (light->shadow != Shadows::None) {
		DirectionalLight* dirLight = (DirectionalLight*) light;
		//directional light only needs one shadow map texture
		//light camera is supposed to be setup so that ortho frustum contains all that the main camera sees
		float quantizeFactor = 0;
		std::vector<glm::vec3> frustumCorners;
		if (dirLight->getShadowMethod() == DirectionalShadowMethods::Basic) {
			frustumCorners = m_camera->getFrustumCorners();
			quantizeFactor = m_camera->getFar() * 0.3f;
		} else if (dirLight->getShadowMethod() == DirectionalShadowMethods::Near) {
			Camera newCamera;
			newCamera.initPerspective(m_camera->getFov(),
									  m_camera->getAspectRatio(),
									  m_camera->getNear(), 
									  m_camera->getFar() * dirLight->getShadowMethodValue());
			newCamera.setTransform(m_camera->getTransform());
			frustumCorners = newCamera.getFrustumCorners();
			quantizeFactor = m_camera->getFar() * dirLight->getShadowMethodValue() * 0.3f;
		}
		glm::mat4 lightView = light->getTransform();
		glm::mat4 invLightView = glm::inverse(lightView);
							
		for (int j = 0; j < 8; ++j) {
			frustumCorners[j] = glm::vec3(lightView * glm::vec4(frustumCorners[j], 1));
			frustumCorners[j].x = glm::ceil(frustumCorners[j].x / quantizeFactor) * quantizeFactor;
			frustumCorners[j].y = glm::ceil(frustumCorners[j].y / quantizeFactor) * quantizeFactor;
			frustumCorners[j].z = glm::ceil(frustumCorners[j].z / quantizeFactor) * quantizeFactor;
		}

		BoundingBox lightBox(frustumCorners);
		lightBox.max.z += 100;
		lightBox.min.z -= 100;

		glm::vec3 boxSize = lightBox.max - lightBox.min;
		glm::vec3 halfBoxSize = boxSize * 0.5f;

		glm::vec3 lightPosition = lightBox.min + halfBoxSize;
		lightPosition.z = lightBox.min.z;

		lightPosition = glm::vec3(invLightView * glm::vec4(lightPosition, 1));

		shadowMapCamera->lookAt(lightPosition,
								lightPosition + light->getForward(),
								light->getUp());
		shadowMapCamera->setProjection(glm::ortho(-boxSize.x, boxSize.x, -boxSize.y, boxSize.y, -boxSize.z, boxSize.z));

		ShaderProgram* depthShader = &m_allShaders.esmDepth;
		if (light->shadow == Shadows::VSM) {
			depthShader = &m_allShaders.vsmDepth;
		}

		m_shadowMap.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderScene(depthShader, shadowMapCamera, light);
		m_shadowMap.unbind();
	}
}

ShaderProgram* Stage::getCorrectDirectionalLightShadowShader(Light* light) {
	if (light->shadow == Shadows::Basic) {
		return &m_allShaders.dirBasic;
	} else if (light->shadow == Shadows::PCF) {
		return &m_allShaders.dirPcf;
	} else if (light->shadow == Shadows::VSM) {
		return &m_allShaders.dirVsm;
	} else if (light->shadow == Shadows::ESM) {
		return &m_allShaders.dirEsm;
	}
	return &m_allShaders.dirNoShadow;
}

void Stage::clearScreen(void) {
	glClearColor(m_bgColor.r, m_bgColor.g, m_bgColor.b, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
}

void Stage::end(void) {
	m_running = false;
}

void Stage::renderScene(ShaderProgram *currentShader, Camera* renderCamera, Light* renderLight, Light* light, Camera* shadowMapCamera, BaseShadowMap* shadowMap) {
	if (currentShader != 0) {
		currentShader->bind();
		renderCamera->bindMatrices(currentShader, "projectionMatrix", "viewMatrix");
		if (light != 0) light->bind(currentShader);
		if (shadowMapCamera != 0) shadowMapCamera->bindMatrices(currentShader, "lightProjView");
		if (shadowMap != 0) {
			shadowMap->bindTexture(currentShader, 3, "shadowMap");
			glm::vec2 pixelOffset(1.0f / float(shadowMap->getWidth()), 1.0f / float(shadowMap->getHeight()));
			glUniform2fv(currentShader->getUniformLocation("pixelOffset"), 1, glm::value_ptr(pixelOffset));
		}
		for (unsigned int j = 0; j < m_meshes.size(); ++j) {
			if (renderLight != 0 && renderLight->getBoundingSphere().radius > 0) {
				if (!renderLight->getBoundingSphere().intersect(m_meshes[j]->getBoundingSphere())) {
					continue;
				}
			}
			if (m_meshes[j]->bothSides == true) {
				glUniform1i(currentShader->getUniformLocation("bothSides"), GL_TRUE);
				glDisable(GL_CULL_FACE);
			} else {
				glUniform1i(currentShader->getUniformLocation("bothSides"), GL_FALSE);
				glEnable(GL_CULL_FACE);
			}
			glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(m_camera->getTransform() * m_meshes[j]->getTransform())));
			glUniformMatrix3fv(currentShader->getUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
			m_meshes[j]->render(currentShader);
		}
		if (shadowMap != 0) shadowMap->unbindTexture();
		currentShader->unbind();
	}
}

void Stage::add(Camera* camera) {
	m_camera = camera;
}

void Stage::add(Mesh* mesh) {
	if (std::find(m_meshes.begin(), m_meshes.end(), mesh) == m_meshes.end()) {
		m_meshes.push_back(mesh);
		m_meshes.back()->geometry->createBuffers();
		m_meshes.back()->material->createBuffers();
	}
}

void Stage::add(Light* light) {
	if (std::find(m_lights.begin(), m_lights.end(), light) == m_lights.end()) {
		m_lights.push_back(light);
	}
}

void Stage::remove(Mesh* mesh) {
	std::vector<Mesh*>::iterator iter = std::find(m_meshes.begin(), m_meshes.end(), mesh);
	if (iter != m_meshes.end()) {
		m_meshes[iter - m_meshes.begin()]->geometry->deleteBuffers();
		m_meshes[iter - m_meshes.begin()]->material->deleteBuffers();
		m_meshes.erase(iter);
	}
}

void Stage::remove(Light* light) {
	std::vector<Light*>::iterator iter = std::find(m_lights.begin(), m_lights.end(), light);
	if (iter != m_lights.end()) {
		m_lights.erase(iter);
	}
}

void Stage::setUpdateCallback(void (*callback)(float)) {
	updateCallback = callback;
}

int Stage::getWidth(void) {
	return m_width;
}

int Stage::getHeight(void) {
	return m_height;
}

int Stage::getFps(void) {
	return m_fps;
}

void Stage::setBackgroundColor(float r, float g, float b) {
	m_bgColor = glm::vec3(r, g, b);
}