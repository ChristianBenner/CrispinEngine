#include "Button.h"
#include <SDL2\SDL_mouse.h>

namespace Crispin {
	Button::Button(Crispin::InputManager* input, Crispin::Camera2D* camera, Crispin::SpriteBatch* batch) {
		m_input = input;
		m_UIBatch = batch;
		m_camera = camera;
	}

	Button::~Button()
	{
		destroy();
	}

	short Button::update() {
		if (isMouseOver(m_input->getMousePos(), m_camera)) {
			if (m_clickOnPos) {
				if (m_input->isKeyDown(SDL_BUTTON_LEFT)) {
					m_colour = Crispin::ColorRGBA8(120, 120, 120, 255);
					return 3;
				}
				else {
					return 4;
				}
			}
			else {
				if (m_input->isKeyPressed(SDL_BUTTON_LEFT)) {
					m_clickOnPos = true;
					return 2;
				}
			}

			m_colour = Crispin::ColorRGBA8(200, 200, 200, 255);
			return 1;
		}
		else {
			m_colour = Crispin::ColorRGBA8(255, 255, 255, 255);
			m_clickOnPos = false;
		}
		
		return 0;
	}
}