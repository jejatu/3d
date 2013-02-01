#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"

class Material {
public:
	Material(void);
	~Material(void);
	virtual void createBuffers(void);
	virtual void deleteBuffers(void);
	virtual void bind(ShaderProgram *shader);
	virtual	void unbind();

protected:
	std::string m_colorMapFilename;
	std::string m_normalMapFilename;
	std::string m_specularMapFilename;
	GLuint m_colorMap;
	GLuint m_normalMap;
	GLuint m_specularMap;
	glm::vec3 m_color;
};

