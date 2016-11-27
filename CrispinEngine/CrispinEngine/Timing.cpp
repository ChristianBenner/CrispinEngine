#include "timing.h"

namespace Crispin {
	FpsLimiter::FpsLimiter() {

	}

	void FpsLimiter::init(float maxFPS) {
		setMaxFPS(maxFPS);
	}

	void FpsLimiter::setMaxFPS(float maxFPS) {
		m_maxFPS = maxFPS;
	}

	void FpsLimiter::begin() {
		m_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::end() {
		calcFPS();

		Uint32 frameTicks = SDL_GetTicks() - m_startTicks;
		if ((1000 / m_maxFPS) > frameTicks) {
			SDL_Delay((Uint32)(1000 / m_maxFPS) - frameTicks);
		}

		return m_FPS;
	}

	void FpsLimiter::calcFPS() {
		static const int NUM_SAMPLES = 20;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		//get current ticks/time
		static Uint32 prevtick = SDL_GetTicks();
		Uint32 currentTicks = SDL_GetTicks();

		m_frame_time = currentTicks - prevtick;
		frameTimes[currentFrame % NUM_SAMPLES] = m_frame_time;

		prevtick = currentTicks;
		int count;
		currentFrame++;
		if (currentFrame < NUM_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0) {
			m_FPS = 1000.0f / frameTimeAverage;
		}
		else {
			m_FPS = 60;
		}
	}
}