#include "image.h"

using namespace Crispin;
GLTexture Image::loadPNG(std::string filepath) {
	GLTexture texture = {};

	std::vector<unsigned char> out, in;
	unsigned long int width, height;
	if (FileIO::readFileToBuffer(filepath, in) == false) {
		FatalError("Could not read PNG to buffer");
	}

	int err = decodePNG(out, width, height, &(in[0]), in.size(), true);
	if (err != 0) {
		FatalError("PNG Decode failed [" + filepath + "]");
	}

	texture.width = width;
	texture.height = height;

	glGenTextures(1, &(texture.ID));
	glBindTexture(GL_TEXTURE_2D, texture.ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, false, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture.ID);

	return texture;
}