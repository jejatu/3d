#include "Material.h"

Material::Material(void) {
	m_colorMap = 0;
	m_normalMap = 0;
	m_specularMap = 0;
	m_colorMapFilename = "";
	m_normalMapFilename = "";
	m_specularMapFilename = "";
	m_color = glm::vec3(1, 1, 1);
}

Material::~Material(void) {

}

void Material::createBuffers(void) {

}

void Material::deleteBuffers(void) {

}

void Material::bind(ShaderProgram *shader) {

}

void Material::unbind() {

}