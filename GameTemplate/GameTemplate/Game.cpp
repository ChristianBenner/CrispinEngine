// Local imports
#include "Game.h"
//#include "IntroCrispin.h"
#include <CrispinEngine\CrispinIntro.h>

// Library/engine imports
#include <CrispinEngine\Managers\Engine.h>

Game::Game() : m_game_name("My Game"),
m_window_width(1280),
m_window_height(720),
m_max_fps(60.0f)
{
}

Game::~Game()
{
	m_audio.removeMusic(&m_music);
	m_audio.destroy();
}

short Game::run(const int& argc, char* argv[]) {
	/* Interpret the arguments if used */

	// Initiate game
	init();

	// Start loop
	loop();

	// Return 0 for success
	return 0;
}

short Game::init() {
	// Engine
	Crispin::init();

	// Window
	m_window.create(m_game_name, m_window_width, m_window_height, Crispin::INVISIBLE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	SDL_GL_SetSwapInterval(1);

	// Audio engine
	m_audio.init(MIX_INIT_OGG);
	m_music = m_audio.loadMusic("Audio/SFX/test.wav");

	// FPS Manager
	m_timer.init(m_max_fps);

	// Stages to array
	m_stages.push_back(new SceneData(new Crispin::Scene::CrispinIntro(&m_window, &m_audio), 0));
	return 0;
}

short Game::loop() {
	while (m_gameState == PlayState::PLAY) {
		// FPS Manager
		m_timer.begin();

		// Input management
		processInput();

		// Update and draw current stage
		update();

		bool onStage = false;
		for (std::vector<SceneData*>::iterator s = m_stages.begin(); s != m_stages.end()
			&& !onStage; s++) {
			onStage = (*s)->p_ID == m_currentStage;
			if (onStage) {
				if (!(*s)->p_stage->update(&m_currentStage)) {
					// If stage no longer in use, de-initialize
					(*s)->p_stage->destroy();
					(*s)->p_stage = nullptr;
				}else{
					m_window.setVisible(true);
					(*s)->p_stage->draw();
				}
			}
		}

		// Buffer swap
		m_window.swapBuffer();

		// End FPS management
		m_current_fps = m_timer.end();
	}
	return 0;
}

// Game core update function, will update all the time
void Game::update() {
	// Music interaction
	if (m_input.isKeyPressed(SDLK_a)) {
		m_music.play(-1);
	}
	if (m_input.isKeyPressed(SDLK_s)) {
		m_music.fadeOut(5000);
		if (!m_music.isPlaying()) {
			m_audio.removeMusic(&m_music);
		}
	}
}

void Game::processInput() {
	m_input.update();

	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			m_gameState = PlayState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_input.setMousePos((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_input.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_input.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_input.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_input.releaseKey(evnt.button.button);
			break;
		}
	}
}