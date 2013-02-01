#include "Camera.h"

Camera::Camera(void) : Object3d()  {

}

Camera::~Camera(void) {

}

void Camera::initPerspective(float fov, float aspect, float near, float far) {
	m_projection = glm::perspective(fov, aspect, near, far);
	m_fov = fov;
	m_aspect = aspect;
	m_near = near;
	m_far = far;
}

void Camera::initOrtho(float left, float right, float bottom, float top, float near, float far) {
	m_projection = glm::ortho(left, right, bottom, top, near, far);
	m_fov = 0;
	m_aspect = 0;
	m_near = near;
	m_far = far;
}

void Camera::bindMatrices(ShaderProgram* shader, const std::string& viewProjUniform) {
	glm::mat4 viewProj = m_projection * m_transform;
	glUniformMatrix4fv(shader->getUniformLocation(viewProjUniform), 1, GL_FALSE, glm::value_ptr(viewProj));
}

void Camera::bindMatrices(ShaderProgram* shader, const std::string& projUniform, const std::string& viewUniform) {
	glUniformMatrix4fv(shader->getUniformLocation(projUniform), 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(shader->getUniformLocation(viewUniform), 1, GL_FALSE, glm::value_ptr(m_transform));
}

void Camera::lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) {
	m_transform = glm::lookAt(eye, center, up);
}

void Camera::calculateFrustumCorners(void) {
	glm::vec3 up = getUp();
	glm::vec3 forward = getForward();
	glm::vec3 right = getRight();
	glm::vec3 center = getPosition();

	glm::vec3 fc = center + forward * m_far;
	glm::vec3 nc = center + forward * m_near;

	float fovInRadians = m_fov / 180.0f * 3.141592f;
	float nearHeight = glm::tan(fovInRadians / 2.0f) * m_near;
	float nearWidth = nearHeight * m_aspect;
	float farHeight = glm::tan(fovInRadians / 2.0f) * m_far;
	float farWidth = farHeight * m_aspect;

	if (m_frustumCorners.size() != 8) m_frustumCorners.resize(8);

	m_frustumCorners[0] = nc - up * nearHeight - right * nearWidth;
	m_frustumCorners[1] = nc + up * nearHeight - right * nearWidth;
	m_frustumCorners[2] = nc + up * nearHeight + right * nearWidth;
	m_frustumCorners[3] = nc - up * nearHeight + right * nearWidth;

	m_frustumCorners[4] = fc - up * farHeight - right * farWidth;
	m_frustumCorners[5] = fc + up * farHeight - right * farWidth;
	m_frustumCorners[6] = fc + up * farHeight + right * farWidth;
	m_frustumCorners[7] = fc - up * farHeight + right * farWidth;

}

std::vector<glm::vec3> Camera::getFrustumCorners(void) {
	calculateFrustumCorners();
	return m_frustumCorners;
}

glm::vec3 Camera::getPosition(void) {
	glm::mat4 invTransform = glm::inverse(getTransform());
	return glm::vec3(invTransform[3].x, invTransform[3].y, invTransform[3].z);
}

glm::vec3 Camera::getForward(void) {
	return glm::normalize(glm::vec3(-m_transform[0].z, -m_transform[1].z, -m_transform[2].z));
}

glm::vec3 Camera::getUp(void) {
	return glm::normalize(glm::vec3(m_transform[0].y, m_transform[1].y, m_transform[2].y));
}

glm::vec3 Camera::getRight(void) {
	return glm::normalize(glm::vec3(m_transform[0].x, m_transform[1].x, m_transform[2].x));
}

glm::mat4 Camera::getProjection(void) {
	return m_projection;
}

BoundingBox Camera::getBoundingBox(void) {
	glm::vec4 minNDC(-1, -1, -1, 1);
	glm::vec4 maxNDC(-1, -1, 1, 1);
	glm::mat4 invProj = glm::inverse(m_projection);
	glm::vec4 minWorld = invProj * minNDC;
	glm::vec4 maxWorld = invProj * maxNDC;
	minWorld /= minWorld.w;
	maxWorld /= maxWorld.w;
	return BoundingBox(glm::vec3(-maxWorld), glm::vec3(maxWorld));
}

void Camera::setProjection(const glm::mat4& projection) {
	m_projection = projection;
}

void Camera::setPosition(float x, float y, float z) {
	glm::vec3 position(x, y, z);
	setPosition(position);
}

void Camera::setPosition(const glm::vec3& position) {
	lookAt(position, getForward(), getUp());
}

float Camera::getNear(void) {
	return m_near;
}

float Camera::getFar(void) {
	return m_far;
}

float Camera::getFov(void) {
	return m_fov;
}

float Camera::getAspectRatio(void) {
	return m_aspect;
}
