#pragma once
#include <GL/glew.h>
#include <string>

namespace Crispin {
	struct GLTexture {
		GLuint ID;
		int width;
		int height;

		std::string filepath;
	};
}