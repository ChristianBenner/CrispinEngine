#include "Statements.h"
#include <SDL2/SDL.h>
#include <windows.h>

namespace Crispin {
	void FatalError(std::string info) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		printf("FATAL ERROR: %s\n", info.c_str());
		SetConsoleTextAttribute(hConsole, 7);
		system("PAUSE");
		SDL_Quit();
		exit(1);
	}

	void Warning(std::string info) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		printf("Warning: %s\n", info.c_str());
		SetConsoleTextAttribute(hConsole, 7);
	}

	void InitializationStatement(std::string info) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 10);
		printf("%s\n", info.c_str());
		SetConsoleTextAttribute(hConsole, 7);
	}
}