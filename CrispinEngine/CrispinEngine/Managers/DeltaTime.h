/*
This is a timing calculating class developed for the Crispin
Engine

Use it for any of your projects, commercial or otherwise,
free of charge, but do not remove this disclaimer.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

March 26 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

#pragma once

#ifndef DeltaTime_h__
#define DeltaTime_h__

#include "../Statements.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>
#include <chrono>

namespace Crispin {
	// Data only
	struct occurence {
		occurence(int FPS) {
			m_FPS = FPS;
		}

		int m_FPS;
		int m_m_occurences = 0;
	};

	// Calculate how much physics should speed up
	class DeltaTime
	{
		// Calculating variables
		const int MAXIMUM_PHYSICS_STEPS = 6;
		const int MODAL_CALCULATION_CYCLES = 100;

		const float DESIRED_UPDATE_RATE = 60.0f;
		const float MAX_DELTA_TIME = 1.0f;
		const float RECALCULATE_AMPLITUDE = 4.0f;
	public:
		DeltaTime();
		~DeltaTime();

		void finishCalculation(const float& deltaTime);

		int getMaximumPhysicsSteps();

		float calculate();
		float getTotalDeltaTime();
		float fps();
	private:
		void addOccurence(const int& FPS);
		void calculateModal(const float& fps);
		void calculateMean(const float& fps);

		int getFPS();
		int round_int(const float& r);

		int m_modalCycles = MODAL_CALCULATION_CYCLES;
		int m_uploadFPS;

		float m_meanUploadFPS;
		float m_deltaTime = MAX_DELTA_TIME;
		float m_previousTicks;
		float m_totalDeltaTime;
		float m_count = 0.0f;

		bool m_timeCalculated = false;
		bool m_isInit = false;

		std::vector<occurence> m_occurences;

		void calculateFPS();
		float m_FPS = 60.0f;
		Uint32 m_frame_time;
	};
}

#endif // DeltaTime_h__