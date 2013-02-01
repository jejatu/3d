#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
class Shader {
public:
	Shader(GLenum type, const std::string& shaderCode);
	~Shader(void);
	GLuint getHandle(void);
	void dispose(void);

private:
	GLuint m_handle;
};

