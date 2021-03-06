#pragma once

// Library/engine imports
#include <CrispinEngine\Managers\Window.h>
#include <CrispinEngine\Managers\Audio.h>
#include <CrispinEngine\Managers\Timing.h>
#include <CrispinEngine\Managers\InputManager.h>
#include <CrispinEngine\Scene.h>

enum PlayState { PLAY, EXIT };

class Game
{
public:
	Game();
	~Game();

	// Public functions
	short run(const int& argc, char* argv[]);

private:
	// Functions
	short init(),
		loop();
	void processInput();
	void update();

	// Objects
	Crispin::Window m_window;
	Crispin::AudioManager m_audio;
	Crispin::Music m_music;
	bool m_panMax;

	Crispin::FpsLimiter m_timer;
	Crispin::InputManager m_input;
	Crispin::SceneManager m_sceneManager;

	// Data
	std::string m_game_name;
	int m_window_width;
	int m_window_height;
	float m_max_fps;
	float m_current_fps = 0.0f;
	PlayState m_gameState = PlayState::PLAY;
	std::vector<Crispin::SceneData*> m_stages;
	short m_currentStage = 0;
};

