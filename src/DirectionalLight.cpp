#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(void) : Light() {
	m_type = LightTypes::DirectionalLight;
	m_shadowMethod = DirectionalShadowMethods::Basic;
	m_shadowMethodValue = 0;
}

DirectionalLight::~DirectionalLight(void) {

}

void DirectionalLight::bind(ShaderProgram *shader) {
	glUniform3fv(shader->getUniformLocation("lightDir"), 1, glm::value_ptr(-getForward()));
	bindProperties(shader);
}

void DirectionalLight::setDirection(float x, float y, float z) {
	setDirection(glm::vec3(x, y, z));
}

void DirectionalLight::setDirection(const glm::vec3& direction) {
	glm::vec3 forward = glm::normalize(direction);
	glm::vec3 right = glm::cross(forward, glm::vec3(0, 1, 0));
	if (glm::length(right) == 0) right = glm::cross(forward, glm::vec3(0, 0, 1));
	glm::vec3 up = glm::cross(right, forward);
	m_transform = glm::lookAt(glm::vec3(0, 0, 0), forward, up);
}

glm::vec3 DirectionalLight::getPosition(void) {
	glm::mat4 invTransform = glm::inverse(getTransform());
	return glm::vec3(invTransform[3].x, invTransform[3].y, invTransform[3].z);
}

glm::vec3 DirectionalLight::getForward(void) {
	return glm::normalize(glm::vec3(-m_transform[0].z, -m_transform[1].z, -m_transform[2].z));
}

glm::vec3 DirectionalLight::getUp(void) {
	return glm::normalize(glm::vec3(m_transform[0].y, m_transform[1].y, m_transform[2].y));
}

glm::vec3 DirectionalLight::getRight(void) {
	return glm::normalize(glm::vec3(m_transform[0].x, m_transform[1].x, m_transform[2].x));
}

void DirectionalLight::setShadowMethod(DirectionalShadowMethods::DirectionalShadowMethod shadowMethod, float shadowMethodValue) {
	m_shadowMethod = shadowMethod;
	m_shadowMethodValue = shadowMethodValue;
}

DirectionalShadowMethods::DirectionalShadowMethod DirectionalLight::getShadowMethod(void) {
	return m_shadowMethod;
}

float DirectionalLight::getShadowMethodValue(void) {
	return m_shadowMethodValue;
}