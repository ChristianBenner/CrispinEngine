#include "resource.h"

namespace Crispin {

	TextureCache Resource::m_textureCache;

	GLTexture Resource::getTexture(std::string filepath) {
		return m_textureCache.getTexture(filepath);
	}

	void Resource::removeTexture(GLTexture* tex) {
		m_textureCache.removeTexture(tex->filepath);
	}
}