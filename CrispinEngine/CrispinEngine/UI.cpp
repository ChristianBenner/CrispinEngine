#include "UI.h"
#include "Loading\Resource.h"

namespace Crispin {
	UI::UI(Crispin::SpriteBatch* batch)
	{
		m_UIBatch = batch;
	}

	UI::~UI()
	{
		destroy();
	}

	void UI::destroy() {
		if (m_textureSet) {
			Crispin::Resource::removeTexture(&m_texture);
		}
	}

	bool UI::isMouseOver(const glm::vec2& mousePos, Crispin::Camera2D* camera) {
		glm::vec2 posOnScreen = camera->convertScreenToWorld(m_position);
		if (mousePos.x > posOnScreen.x &&
			mousePos.x < posOnScreen.x + m_size.x &&
			mousePos.y > posOnScreen.y - m_size.y &&
			mousePos.y < posOnScreen.y) {
			return true;
		}
		else {
			return false;
		}
	}

	void UI::setPosition(Crispin::Camera2D* camera, const glm::vec2& position) {
		m_position = camera->convertScreenToWorld(position);
	}

	void UI::setSize(const glm::vec2& size) {
		m_size = size;
	}

	void UI::setTexture(Crispin::GLTexture* tex) {
		m_textureSet = true;
		if (m_size.x == 0.0f && m_size.y == 0.0f) {
			setSize(glm::vec2(tex->width, tex->height));
		}

		m_texture = *tex;
	}

	void UI::setTexture(const std::string& filepath) {
		m_textureSet = true;
		m_texture = Crispin::Resource::getTexture(filepath);

		if (m_size.x == 0.0f && m_size.y == 0.0f) {
			setSize(glm::vec2(m_texture.width, m_texture.height));
		}
	}

	// Just draw border unless texture supplied
	void UI::draw(const float& depth) {
		if (!m_textureSet) {
			// Draw border
			//m_UIBatch->drawLine();
			//m_UIBatch->drawLine();
			//m_UIBatch->drawLine();
			//m_UIBatch->drawLine();
		}
		else {
			// Draw texture
			m_UIBatch->draw(glm::vec4(getPosition(), getSize()), glm::vec4(0.0f, 0.f, 1.0f, 1.0f),
				m_texture.ID, depth, 
				Crispin::ColorRGBA8(m_colour.r, m_colour.g, m_colour.b, m_colour.a * m_alphaModifier));
		}
	}
}