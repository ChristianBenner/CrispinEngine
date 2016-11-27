#include "shader.h"

using namespace Crispin;
Shader::Shader(){ }

Shader::~Shader()
{
	if (m_vertexShaderID != NULL) {
		glDeleteShader(m_vertexShaderID);
	}
	if (m_fragmentShaderID != NULL) {
		glDeleteShader(m_fragmentShaderID);
	}
}

void Shader::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	m_programID = glCreateProgram();

	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0) {
		FatalError("Could not create vertex shader ID");
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0) {
		FatalError("Could not create fragment Shader ID");
	}

	compileShader(vertexShaderFilePath, m_vertexShaderID);
	compileShader(fragmentShaderFilePath, m_fragmentShaderID);
}

void Shader::compileShader(const std::string& filepath, GLuint ID) {
	std::ifstream file(filepath);
	if (file.fail()) {
		perror(filepath.c_str());
		FatalError("Failed to open " + ID);
	}

	std::string fileContent = "";
	std::string line;
	while (std::getline(file, line)) {
		fileContent += line + "\n";
	}
	file.close();

	const char* contentsPtr = fileContent.c_str();
	glShaderSource(ID, 1, &contentsPtr, nullptr);
	glCompileShader(ID);

	GLint isCompiled = 0;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(ID, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(ID);
		printf("%s\n", &errorLog[0]);
		FatalError("Shader [" + filepath + "] failed to compile");
	}
}

void Shader::linkShaders() {
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	glLinkProgram(m_programID);

	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

		printf("%s\n", &infoLog[0]);
		FatalError("Shaders failed to link");

		glDeleteProgram(m_programID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);
	}

	// Detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
};

void Shader::addAttribute(const std::string &attributeName) {
	glBindAttribLocation(m_programID, m_attributes++, attributeName.c_str());
}

void Shader::use() {
	glUseProgram(m_programID);
	for (int i = 0; i < m_attributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void Shader::unuse() {
	glUseProgram(0);
	for (int i = 0; i < m_attributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLint Shader::getUniformLocation(const std::string uniformName) {
	GLint loc = glGetUniformLocation(m_programID, uniformName.c_str());
	if (loc == GL_INVALID_INDEX) {
		FatalError("Uniform variable: " + uniformName + " not found");
	}
	return loc;
}