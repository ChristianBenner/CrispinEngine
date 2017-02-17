#include "Window.h"
#include "../Statements.h"

namespace Crispin {
	Window::Window()
	{
		// Empty
	}


	Window::~Window()
	{
		// Empty
	}

	void Window::destroy() {
		SDL_DestroyRenderer(SDL_GetRenderer(m_sdlWindow));
		SDL_DestroyWindow(m_sdlWindow);
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
		// More advanced screen sizing stuff when resize
		m_screenHeight = screenHeight;
		m_screenWidth = screenWidth;

		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}
		
		//Open an SDL window
		m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (m_sdlWindow == nullptr) {
			FatalError("SDL Window could not be created!");
		}

		//Set up OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
		if (glContext == nullptr) {
			FatalError("SDL_GL context could not be created!");
		}

		//Set up glew
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			FatalError("Could not initialize glew!");
		}

		//Print OpenGL version
		std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

		//Set the background color
		glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

		//Set vsync
		SDL_GL_SetSwapInterval(0);

		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(m_sdlWindow);
	}

	void Window::showMouse(bool show) {
		if (show) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else {
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
	}

	void Window::setVisible(bool visible){
		if (visible) {
			SDL_ShowWindow(m_sdlWindow);
		}
		else {
			SDL_HideWindow(m_sdlWindow);
		}
	}
}