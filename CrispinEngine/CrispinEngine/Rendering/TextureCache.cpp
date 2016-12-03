#include "TextureCache.h"
#include "Image.h"
#include <iostream>

namespace Crispin {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}


	GLTexture TextureCache::getTexture(std::string texturePath) {

		//lookup the texture and see if its in the map
		auto mit = m_textureMap.find(texturePath);

		//check if its not in the map
		if (mit == m_textureMap.end()) {
			//Load the texture
			GLTexture newTexture = Image::loadPNG(texturePath);

			//Insert it into the map
			m_textureMap.insert(make_pair(texturePath, newTexture));

			newTexture.filepath = texturePath;
			return newTexture;
		}

		return mit->second;
	}

	void TextureCache::removeTexture(std::string texturePath) {
		Warning("Called remove texture for: " + texturePath);

		// Free texture from video memory
		auto it = m_textureMap.find(texturePath);
		glDeleteTextures(1, &it->second.ID);

		// Remove from map
		m_textureMap.erase(it);
	}
}