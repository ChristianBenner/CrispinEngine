#include "FileIO.h"

bool Crispin::FileIO::readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer) {
	std::ifstream stream(filepath, std::ios::binary);
	if (stream.fail()) {
		perror(filepath.c_str());
		Warning("Failed to read [" + filepath + "]");
		return false;
	}

	stream.seekg(0, std::ios::end);
	auto streamSize = stream.tellg();
	stream.seekg(0, std::ios::beg);
	streamSize -= stream.tellg();

	buffer.resize((unsigned int) streamSize);
	stream.read((char *)&buffer[0], streamSize);
	stream.close();
	return true;
}