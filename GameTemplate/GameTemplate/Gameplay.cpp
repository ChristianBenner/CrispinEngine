#include "Gameplay.h"

Gameplay::Gameplay(Crispin::Window* window, Crispin::AudioManager* audio)
{
	// Pass through pointers to variables that will be used in initialization process
	m_window = window;
	m_audio = audio;
}

void Gameplay::destroy()
{
	// Remove loaded audio
	m_audio->removeSound(&m_walkSound);
	Crispin::Resource::removeTexture(&m_grass);
	Crispin::Resource::removeTexture(&m_player);
}

void Gameplay::init() {
	m_walkSound = m_audio->loadSound("Audio/SFX/step.ogg");

	initShaders();

	m_renderBatch.init();

	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setPosition(glm::vec2(0.0f, 0.0f));
	m_camera.setScale(1.0f);

	// Load textures now (so rendering can happen instantly)
	m_grass = Crispin::Resource::getTexture("Textures/logo/grass.png");
	m_player = Crispin::Resource::getTexture("Textures/logo/player.png");

	//m_walkSound.play();
}

void Gameplay::initShaders() {
	//Color shader
	m_shader.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}

const float STAGE_DURATION = 6; //seconds
bool Gameplay::update(short* currentStage) {
	// Check if stage has been initiated
	if (!m_init) {
		init();
		m_init = true;
	}

	m_camera.update();

	// TODO: Input management here


	return true;
}

void Gameplay::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);

	m_shader.use();

	GLint textureUniform = m_shader.getUniformLocation("texSampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint projectionMatrixUniform = m_shader.getUniformLocation("projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_renderBatch.begin();

	//glClearColor(alpha * (1.0f / 255.0f), alpha * (1.0f / 255.0f), alpha * (1.0f / 255.0f), 1.0f);
	Crispin::ColorRGBA8 whiteColor = Crispin::ColorRGBA8(255, 255, 255, 255);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect = glm::vec4(-m_window->getScreenWidth() / 2.0f, -m_window->getScreenHeight() / 2.0f, m_window->getScreenWidth(), m_window->getScreenHeight());

//	m_introBatch.draw(destRect, uvRect, m_tex_logoRed.ID, 0.0f, Crispin::ColorRGBA8(255, 255, 255, (GLubyte)alpha));
	//if (m_intro_clock < 255.0f) {
//		m_introBatch.draw(destRect, uvRect, m_tex_logoWhite.ID, 0.0f, Crispin::ColorRGBA8(255, 255, 255, 255 - (GLubyte)alpha));
//	}

	m_renderBatch.end();
	m_renderBatch.renderBatch();
	m_shader.unuse();
}
