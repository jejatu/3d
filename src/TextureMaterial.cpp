#include "TextureMaterial.h"

TextureMaterial::TextureMaterial(void) : Material() {

}

TextureMaterial::~TextureMaterial(void) {

}

void TextureMaterial::init(std::string colorMapFilename) {
	m_colorMapFilename = colorMapFilename;
}

void TextureMaterial::init(std::string colorMapFilename, std::string normalMapFilename) {
	m_colorMapFilename = colorMapFilename;
	m_normalMapFilename = normalMapFilename;
}

void TextureMaterial::init(std::string colorMapFilename, std::string normalMapFilename, std::string specularMapFilename) {
	m_colorMapFilename = colorMapFilename;
	m_normalMapFilename = normalMapFilename;
	m_specularMapFilename = specularMapFilename;
}

void TextureMaterial::createBuffers(void) {
	if (m_colorMap == 0) createColorMap(m_colorMapFilename);
	if (m_normalMap == 0) createNormalMap(m_normalMapFilename);
	if (m_specularMap == 0) createSpecularMap(m_specularMapFilename);
}

void TextureMaterial::deleteBuffers(void) {
	if (m_colorMap != 0) glDeleteTextures(1, &m_colorMap);
	if (m_normalMap != 0) glDeleteTextures(1, &m_normalMap);
	if (m_specularMap != 0) glDeleteTextures(1, &m_specularMap);
	m_colorMap = 0;
	m_normalMap = 0;
	m_specularMap = 0;
}

void TextureMaterial::createColorMap(std::string filename) {
	if (filename.size() > 0) {
		glGenTextures(1, &m_colorMap);
		glBindTexture(GL_TEXTURE_2D, m_colorMap);
		glfwLoadTexture2D(filename.c_str(), GLFW_BUILD_MIPMAPS_BIT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void TextureMaterial::createNormalMap(std::string filename) {
	if (filename.size() > 0) {
		glGenTextures(1, &m_normalMap);
		glBindTexture(GL_TEXTURE_2D, m_normalMap);
		glfwLoadTexture2D(filename.c_str(), GLFW_BUILD_MIPMAPS_BIT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0); 
	}
}

void TextureMaterial::createSpecularMap(std::string filename) {
	if (filename.size() > 0) {
		glGenTextures(1, &m_specularMap);
		glBindTexture(GL_TEXTURE_2D, m_specularMap);
		glfwLoadTexture2D(filename.c_str(), 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void TextureMaterial::bind(ShaderProgram *shader) {
	glUniform3fv(shader->getUniformLocation("color"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_colorMap);
	glUniform1i(shader->getUniformLocation("colorMap"), 0);
	if (m_normalMap > 0) {
		glUniform1i(shader->getUniformLocation("bumpMapping"), GL_TRUE);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_normalMap);
		glUniform1i(shader->getUniformLocation("normalMap"), 1);
	} else {
		glUniform1i(shader->getUniformLocation("bumpMapping"), GL_FALSE);
	}
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_specularMap);
	glUniform1i(shader->getUniformLocation("specularMap"), 2);
}

void TextureMaterial::unbind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}