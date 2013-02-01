#include "ColorMaterial.h"

ColorMaterial::ColorMaterial(void) : Material() {
	m_lastShader = 0;
}

ColorMaterial::~ColorMaterial(void) {

}

void ColorMaterial::init(float r, float g, float b) {
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
}

void ColorMaterial::bind(ShaderProgram *shader) {
	glUniform3fv(shader->getUniformLocation("color"), 1, glm::value_ptr(m_color));
	glUniform1i(shader->getUniformLocation("bumpMapping"), GL_FALSE);
	m_lastShader = shader;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

void ColorMaterial::unbind() {
	if (m_lastShader != 0) glUniform3fv(m_lastShader->getUniformLocation("color"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
}