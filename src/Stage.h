#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "ShadowMap.h"
#include "ShadowCubeMap.h"
#include "AllShaders.h"

class Stage {
public:
	Stage(void);
	~Stage(void);
	void init(int width, int height, int framerate, int fsaa, bool fullscreen);
	void dispose(void);
	void run(void);
	void end(void);
	void add(Camera* camera);
	void add(Mesh* mesh);
	void add(Light* light);
	void remove(Mesh* mesh);
	void remove(Light* light);
	void setUpdateCallback(void (*callback)(float));
	int getWidth(void);
	int getHeight(void);
	int getFps(void);
	void setBackgroundColor(float r, float g, float b);

private:
	void update(double currentTime);
	void render(void);

	void calculateFps(double currentTime);

	void initGL(void);
	void initShadowMaps(void);
	void initForwardRendering(void);
	void initLightRendering(void);

	void clearScreen(void);
	void renderDepth(void);
	void renderColor(Light* light, int lightIndex, ShaderProgram* colorShader, Camera* shadowMapCamera, BaseShadowMap* baseShadowMap);
	void renderPointLightShadowMap(Light* light, Camera* shadowMapCamera);
	void renderDirectionalLightShadowMap(Light* light, Camera* shadowMapCamera);
	void forwardRender(void);
	void renderScene(ShaderProgram *currentShader, Camera* renderCamera, Light* renderLight = 0, Light* light = 0, Camera* shadowMapCamera = 0, BaseShadowMap* shadowMap = 0);

	ShaderProgram* getCorrectPointLightShadowShader(Light* light);
	ShaderProgram* getCorrectDirectionalLightShadowShader(Light* light);
	
	void (*updateCallback)(float);
	bool m_running;
	bool m_terminated;

	//opengl
	Camera* m_camera;
	std::vector<Mesh*> m_meshes;
	std::vector<Light*> m_lights;
	AllShaders m_allShaders;
	ShadowMap m_shadowMap;
	ShadowCubeMap m_shadowCubeMap;

	//stage properties
	int m_width;
	int m_height;
	int m_framerate;
	glm::vec3 m_bgColor;
	bool m_forwardRendering;

	//timing and fps
	int m_fps;
	int m_frame;
	double m_timer;
	double m_lastSecond;
	double m_lastTime;
};

