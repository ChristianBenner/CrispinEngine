#include "DeltaTime.h"
#include <vector>

namespace Crispin {
	DeltaTime::DeltaTime()
	{
		//Empty
	}

	DeltaTime::~DeltaTime()
	{
		// Clear the vector array
		m_occurences.clear();
	}
	
	float DeltaTime::calculate() {
		calculateFPS();

		// If the upload FPS has no value, just use current FPS
		if (!m_isInit) {
			m_uploadFPS = round_int(m_FPS);
			m_isInit = true;
		}

		// If FPS fluctuates by a ratio of 'RECALCULATE_AMPLITUDE'
		if (m_timeCalculated &&
			std::max((float)m_uploadFPS, m_FPS) / std::min((float)m_uploadFPS, m_FPS) >=
			RECALCULATE_AMPLITUDE) {
			// Use mean timing mode
			m_timeCalculated = false;

			// Reset modal timing loop
			m_count = 0.0f;
			m_occurences.clear();
			m_modalCycles = 10;

			Warning("Major FPS fluctation, changing timing modes");
		}

		// Upload FPS to modal calculator
		calculateModal(m_FPS);

		// Mean timing method - instant but fluctuates
		if (!m_timeCalculated) {
			calculateMean(m_FPS);
			m_totalDeltaTime = DESIRED_UPDATE_RATE / m_meanUploadFPS;
		}
		else {
			m_totalDeltaTime = DESIRED_UPDATE_RATE / m_uploadFPS;
		}

		m_deltaTime = std::min(m_totalDeltaTime, MAX_DELTA_TIME);
		return m_deltaTime;
	}

	// Calculate the most occuring FPS
	void DeltaTime::calculateModal(const float& fps) {
		addOccurence(round_int(fps));

		m_count += 1.0f * m_deltaTime; ///work on
		if (m_count >= m_modalCycles) {
			m_uploadFPS = getFPS();

			if (!m_timeCalculated) {
				printf("Delta[%f], Size[%d], FPS[%d]\n",
					m_deltaTime,
					m_occurences.size(),
					m_uploadFPS);
			}

			// Reset modal calculating
			m_occurences.clear();
			m_count = 0.0f;
			m_modalCycles = MODAL_CALCULATION_CYCLES;
			m_timeCalculated = true;
		}
	}

	// Calculate the mean FPS
	void DeltaTime::calculateMean(const float& fps) {
		m_meanUploadFPS = fps;
		static int takeRate = 0;
		static float fpsBuffer = 0;

		fpsBuffer += fps;
		takeRate++;

		// Constantly update the average value
		m_meanUploadFPS = fpsBuffer / takeRate;

		// Reset mean calculating
		if (takeRate > 10) {
			takeRate = 0;
			fpsBuffer = 0;
		}
	}

	// Add an occurence for the modal calculations
	void DeltaTime::addOccurence(const int& FPS) {
		bool makenew = true;
		for (
			std::vector<occurence>::iterator it = m_occurences.begin();
			it != m_occurences.end() && makenew; ++it) {
			if ((int)FPS == it->m_FPS) {
				it->m_m_occurences++;
				makenew = false;
			}
		}

		if (makenew) {
			m_occurences.emplace_back((int)FPS);
		}
	}

	// Get the most occuring FPS value
	int DeltaTime::getFPS() {
		int modalAddress = -1, iterated = -1, mostm_occurences = 0;

		// Iterate through whole vector array and determine most occuring FPS
		for (std::vector<occurence>::iterator it = m_occurences.begin(); 
		it != m_occurences.end(); ++it) {
			iterated++;
			// If th
			if (it->m_m_occurences > mostm_occurences) {
				modalAddress = iterated;
				mostm_occurences = it->m_m_occurences;
			}
		}

		// If the iteration is pointing to a value
		if (modalAddress != -1) {
			return m_occurences[modalAddress].m_FPS;
		}
		else {
			// If no modal is found, return 60
			return 60;
		}
	}

	// Round a float to the nearest integer
	int DeltaTime::round_int(const float& r) {
		return (int)((r > 0.0f) ? (r + 0.5f) : (r - 0.5f));
	}

	void DeltaTime::finishCalculation(const float& deltaTime) {
		m_totalDeltaTime -= deltaTime;
	}

	int DeltaTime::getMaximumPhysicsSteps() {
		return MAXIMUM_PHYSICS_STEPS;
	}

	float DeltaTime::getTotalDeltaTime() {
		return m_totalDeltaTime;
	}

	void DeltaTime::calculateFPS() {
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

	float DeltaTime::fps() {
		return m_FPS;
	}
}