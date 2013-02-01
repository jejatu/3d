#include "PointLight.h"

PointLight::PointLight(void) : Light() {
	m_type = LightTypes::PointLight;
}

PointLight::~PointLight(void) {

}

void PointLight::bind(ShaderProgram *shader) {
	glUniform3fv(shader->getUniformLocation("lightPos"), 1, glm::value_ptr(getPosition()));
	bindProperties(shader);
}
