#pragma once
#include "Scene.h"
#include "Managers\Window.h"
#include "Rendering\SpriteBatch.h"
#include "Rendering\Camera2D.h"
#include "Rendering\Shader.h"

namespace Crispin {
	namespace Scenes {
		class CrispinIntro : public Scene
		{
		public:
			// Provide the class with all the data it may need in pointers
			CrispinIntro(Crispin::Window* window, Crispin::AudioManager* audio);

			void draw() override;
			bool update() override;

			// Call init if want to initiate early, otherwise it's called automatically
			void init();
			void destroy();
		private:
			void initShaders();

			bool m_init = false;

			Crispin::Window* m_window;
			Crispin::AudioManager* m_audio;

			Crispin::Sound m_introSound;
			Crispin::SpriteBatch m_introBatch;
			Crispin::Camera2D m_camera;
			Crispin::Shader m_shader;
			Crispin::GLTexture m_tex_logoRed, m_tex_logoWhite;

			float m_intro_time = 0.0f;
			float m_intro_clock = 0.0f;
			float alpha = 0.0f;
		};

	}
}


