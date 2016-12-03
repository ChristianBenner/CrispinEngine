/*
This is a window display class developed for the Crispin
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

#ifndef Window_h__
#define Window_h__

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Crispin {
	// Property flags
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags = NULL);

		void swapBuffer();
		void showMouse(bool show);
		void setVisible(bool visible);

		int getScreenWidth() { return m_screenWidth; }
		int getScreenHeight() { return m_screenHeight; }
	private:
		SDL_Window* m_sdlWindow;
		int m_screenWidth;
		int m_screenHeight;
	};
}

#endif