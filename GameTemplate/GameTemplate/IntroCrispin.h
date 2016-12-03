#pragma once

#include "Stage.h"

#include <CrispinEngine\Rendering\SpriteBatch.h>
#include <CrispinEngine\Rendering\Camera2D.h>
#include <CrispinEngine\Rendering\Shader.h>
#include <CrispinEngine\Loading\Resource.h>
#include <CrispinEngine\Managers\Audio.h>
#include <CrispinEngine\Managers\Window.h>

class IntroCrispin : public Stage
{
public:
	// Provide the class with all the data it may need in pointers
	IntroCrispin(Crispin::Window* window, Crispin::AudioManager* audio);
	~IntroCrispin();

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

	Crispin::Sound m_introSound;
	Crispin::SpriteBatch m_introBatch;
	Crispin::Camera2D m_camera;
	Crispin::Shader m_shader;
	Crispin::GLTexture m_tex_logoRed, m_tex_logoWhite;

	float m_intro_time = 0.0f;
	float m_intro_clock = 0.0f;
	float alpha = 0.0f;
};

