/*
This is a timing/fps management class developed for the 
Crispin Engine

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
#include <SDL2/SDL.h>

namespace Crispin {
	class FpsLimiter {
	public:
		FpsLimiter();

		void init(float maxFPS);
		void setMaxFPS(float maxFPS);

		//begin measuring
		void begin();

		//return FPS
		float end();

	private:
		void calcFPS();

		unsigned int m_startTicks;
		float m_maxFPS;
		float m_FPS;
		float m_frame_time;
	};
}