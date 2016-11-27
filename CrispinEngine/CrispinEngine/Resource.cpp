#include "resource.h"

namespace Crispin {

	TextureCache Resource::m_textureCache;

	GLTexture Resource::getTexture(std::string filepath) {
		return m_textureCache.getTexture(filepath);
	}

	void Resource::removeTexture(std::string filepath) {
		m_textureCache.removeTexture(filepath);
	}
}