#pragma once
#include "UI.h"
#include "Managers\InputManager.h"
#include "Rendering\SpriteBatch.h"
#include <type_traits>

namespace Crispin {
	class Button : public Crispin::UI
	{
	public:
		Button() { /*EMPTY*/ }
		Button(Crispin::InputManager* input, Crispin::Camera2D* camera, Crispin::SpriteBatch* batch);
		~Button();

		/* Returns 0 if nothing is interacting,
		Returns 1 if mouse is over
		Returns 2 if mouse has CLICKED the button,
		Returns 3 if mouse is over the button,
		Returns 4 if user has pressed the button*/
		short update();

	private:
		Crispin::InputManager* m_input;
		Crispin::Camera2D* m_camera;

		bool m_clickOnPos = false;
	};
}
