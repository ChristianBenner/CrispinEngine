#pragma once
#include <CrispinEngine\Scene.h>
#include <CrispinEngine\Managers\Window.h>
#include <CrispinEngine\Rendering\SpriteBatch.h>
#include <CrispinEngine\Rendering\Camera2D.h>
#include <CrispinEngine\Rendering\Shader.h>
#include <CrispinEngine\Loading\Resource.h>

class Gameplay : public Crispin::Scene
{
public:
	Gameplay(Crispin::Window* window, Crispin::AudioManager* audio);

	void draw() override;
	bool update(short* currentStage) override;

	// Call init if want to initiate early, otherwise it's called automatically
	void init();
	void destroy();
private:
	void initShaders();

	bool m_init = false;

	Crispin::Window* m_window;
	Crispin::AudioManager* m_audio;

	Crispin::Sound m_walkSound;
	Crispin::SpriteBatch m_renderBatch;
	Crispin::Camera2D m_camera;
	Crispin::Shader m_shader;
	Crispin::GLTexture m_grass, m_player;
};

