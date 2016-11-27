/*
This is a PNG file loading function

Copyright (c) 2005-2010 Lode Vandevenne
*/

#include <vector>

namespace Crispin {
	extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
}