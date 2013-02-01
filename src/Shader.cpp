#include "Shader.h"

Shader::Shader(GLenum type, const std::string& shaderCode) {
	m_handle = glCreateShader(type);
	const char *code = shaderCode.c_str();
	int length = shaderCode.size();
	glShaderSource(m_handle, 1, &code, &length);
	glCompileShader(m_handle);

	GLint compileStatus = 0;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == 0) {
		// compilation failed
		// print logs and delete shader
		GLint logLength;
		char *log;
		glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &logLength);
		log = new char[logLength];
		glGetShaderInfoLog(m_handle, logLength, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
		glDeleteShader(m_handle);
		m_handle = 0;
	}
}

Shader::~Shader(void) {

}

GLuint Shader::getHandle(void) {
	return m_handle;
}

void Shader::dispose(void) {
	if (m_handle != 0) glDeleteShader(m_handle);
	m_handle = 0;
}