#include "BaseShadowMap.h"

BaseShadowMap::BaseShadowMap(void) {
	m_texture = 0;
	m_rbo = 0;
	m_fbo = 0;
}

BaseShadowMap::~BaseShadowMap(void) {
	if (m_texture != 0) glDeleteTextures(1, &m_texture);
	if (m_rbo != 0) glDeleteRenderbuffers(1, &m_rbo);
	if (m_fbo != 0) glDeleteFramebuffers(1, &m_fbo);
	m_texture = 0;
	m_rbo = 0;
	m_fbo = 0;
}

void BaseShadowMap::init(int width, int height) {

}

void BaseShadowMap::bind(void) {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, m_width, m_height);
}

void BaseShadowMap::unbind(void) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BaseShadowMap::bindTexture(ShaderProgram *shader, int textureIndex, const std::string& uniformName) {
	
}

void BaseShadowMap::unbindTexture(void) {

}

int BaseShadowMap::getWidth(void) {
	return m_width;
}

int BaseShadowMap::getHeight(void) {
	return m_height;
}