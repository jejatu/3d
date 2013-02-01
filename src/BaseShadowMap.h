#pragma once
#include <iostream>
#include <GL/glew.h>
#include "ShaderProgram.h"

class BaseShadowMap {
public:
	BaseShadowMap(void);
	virtual ~BaseShadowMap(void);
	virtual void init(int width, int height);
	void bind(void);
	void unbind(void);
	virtual void bindTexture(ShaderProgram *shader, int textureIndex, const std::string& uniformName);
	virtual void unbindTexture(void);
	int getWidth(void);
	int getHeight(void);

protected:
	GLuint m_fbo;
	GLuint m_rbo;
	GLuint m_texture;
	int m_lastTextureIndex;
	int m_width;
	int m_height;
};

