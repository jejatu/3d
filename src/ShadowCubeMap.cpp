#include "ShadowCubeMap.h"

ShadowCubeMap::ShadowCubeMap(void) : BaseShadowMap() {

}

void ShadowCubeMap::init(int width, int height) {
	m_width = width;
	m_height = height;
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	for (int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

	GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "GL_FRAMEBUFFER_COMPLETE failed" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ShadowCubeMap::~ShadowCubeMap(void) {
	
}

void ShadowCubeMap::attach(GLenum target) {
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target, m_texture, 0);
}

void ShadowCubeMap::bindTexture(ShaderProgram *shader, int textureIndex, const std::string& uniformName) {
	glActiveTexture(GL_TEXTURE0 + textureIndex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
    glUniform1i(shader->getUniformLocation(uniformName), textureIndex);
	m_lastTextureIndex = textureIndex;
}

void ShadowCubeMap::unbindTexture(void) {
	glActiveTexture(GL_TEXTURE0 + m_lastTextureIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
