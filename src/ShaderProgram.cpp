#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
	m_program = 0;
}

ShaderProgram::~ShaderProgram(void) {
	for (unsigned int i = 0; i < m_shaders.size(); ++i) {
		if (m_shaders[i] != 0) glDeleteShader(m_shaders[i]);
		m_shaders[i] = 0;
	}
	if (m_program != 0) glDeleteProgram(m_program);
	m_program = 0;
}

void ShaderProgram::addShader(Shader& shader) {
	if (shader.getHandle() > 0) {
		m_shaders.push_back(shader.getHandle());
	}
}

void ShaderProgram::createProgram(void) {
	if (m_shaders.size() > 0) {
		m_program = glCreateProgram();
		for (unsigned int i = 0; i < m_shaders.size(); ++i) {
			glAttachShader(m_program, m_shaders[i]);
		}
		glLinkProgram(m_program);

		GLint linkStatus = 0;
		glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == 0) {
			// linking failed
			// print logs and delete program
			GLint logLength;
			char *log;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
			log = new char[logLength];
			glGetProgramInfoLog(m_program, logLength, 0, log);
			std::cerr << log << std::endl;
			delete[] log;
			glDeleteProgram(m_program);
		}
	}
}

void ShaderProgram::bind(void) {
	glUseProgram(m_program);
}

void ShaderProgram::unbind(void) {
	glUseProgram(0);
}

GLint ShaderProgram::getUniformLocation(std::string uniformName) {
	return glGetUniformLocation(m_program, uniformName.c_str());
}

GLint ShaderProgram::getAttributeLocation(std::string attributeName) {
	return glGetAttribLocation(m_program, attributeName.c_str());
}