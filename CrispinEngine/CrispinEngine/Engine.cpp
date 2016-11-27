#include <SDL2/SDL.h>
#include "Engine.h"

namespace Crispin {
	int init() {
		// Error reporting
		if (int i = SDL_Init(SDL_INIT_EVERYTHING) != 0) { return i; }
		if (int i = SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0){ return i; }
		return 0;
	}
}