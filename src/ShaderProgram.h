#pragma once
#include <vector>
#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram(void);
	ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgram(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader);
	~ShaderProgram(void);
	void addShader(Shader& shader);
	void createProgram(void);
	void bind(void);
	void unbind(void);
	GLint getUniformLocation(std::string uniformName);
	GLint getAttributeLocation(std::string attributeName);
	
private:
	std::vector<GLuint> m_shaders;
	GLuint m_program;
};

