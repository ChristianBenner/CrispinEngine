/*
This is a GLSL shader class developed for the Crispin
Engine

Use it for any of your projects, commercial or otherwise,
free of charge, but do not remove this disclaimer.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

March 26 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

#pragma once
#include <GL/glew.h>
#include <string>
#include "../Statements.h"
#include <fstream>
#include <vector>

namespace Crispin {
	class Shader
	{
	public:
		Shader();
		~Shader();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string &attributeName);
		void use();
		void unuse();

		GLint getUniformLocation(const std::string uniformName);
	private:
		void compileShader(const std::string& filepath, GLuint ID);

		int m_attributes = 0;

		GLuint m_programID = 0;
		GLuint m_fragmentShaderID = 0;
		GLuint m_vertexShaderID = 0;
	};
}