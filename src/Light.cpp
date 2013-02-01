#include "Light.h"

Light::Light(void) : Object3d()  {
	m_type = LightTypes::NoLight;
	shadow = Shadows::None;
	radius = 0;
	color = glm::vec3(1, 1, 1);
}

Light::~Light(void) {

}

void Light::bind(ShaderProgram* shader) {

}

LightTypes::LightType Light::getType(void) {
	return m_type;
}

void Light::bindProperties(ShaderProgram *shader) {
	glUniform3fv(shader->getUniformLocation("ambient"), 1, glm::value_ptr(color * ambient));
	glUniform3fv(shader->getUniformLocation("diffuse"), 1, glm::value_ptr(color * diffuse));
	glUniform3fv(shader->getUniformLocation("specular"), 1, glm::value_ptr(color * specular));
	glUniform1f(shader->getUniformLocation("lightRadius"), radius);
}

BoundingBox Light::getBoundingBox(void) {
	return BoundingBox(getPosition() - radius * 4.0f, getPosition() + radius * 4.0f);
}

BoundingSphere Light::getBoundingSphere(void) {
	return BoundingSphere(getPosition(), radius * 4.0f);
}