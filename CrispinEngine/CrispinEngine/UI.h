#pragma once
#include <glm\glm.hpp>
#include "Objects\Data\GLTexture.h"
#include "Rendering\SpriteBatch.h"
#include "Rendering\Camera2D.h"

namespace Crispin {
	class UI
	{
	public:
		UI() { /*empty*/ }
		UI(Crispin::SpriteBatch* batch);
		~UI();

		bool isMouseOver(const glm::vec2& mousePos, Crispin::Camera2D* camera);

		void setPosition(Crispin::Camera2D* camera, const glm::vec2& position);
		void setSize(const glm::vec2& size);
	//	void setSize(Crispin::GLTexture* tex);

		// If size not set but texture supplied then set size to texture size
		void setTexture(const std::string& filepath);
		void setTexture(Crispin::GLTexture* tex);

		// Just draw border unless texture supplied
		void draw(const float& depth = 1.0f);

		void destroy();

		glm::vec2 getSize() { return m_size; }
		glm::vec2 getPosition() { return m_position; }

		void setAlphaModifier(const float& alpha) {
			m_alphaModifier = alpha;
		}
	protected:
		glm::vec2 m_position;
		glm::vec2 m_size = glm::vec2(0.0f, 0.0f);
		bool m_textureSet = false;
		Crispin::ColorRGBA8 m_colour = Crispin::ColorRGBA8(255, 255, 255, 255);

		Crispin::SpriteBatch* m_UIBatch;

		float m_alphaModifier = 1.0f;
	private:
		Crispin::GLTexture m_texture;
	};
}
