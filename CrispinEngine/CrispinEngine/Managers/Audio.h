#pragma once
#include <string>
#include <map>
#include <vector>

#include <SDL2/SDL_mixer.h>

namespace Crispin {
	class Sound {
	public:
		friend class Audio;

		void play(const int& loops = 0);

		void setPan(const Uint8& left, const Uint8& right);
		void setVolume(const Uint8& volume);

		Uint8 getPanLeft() { return m_panLeft; }
		Uint8 getPanRight() { return m_panRight; }
		
		int getID() { return m_mapPos; }
	private:
		Mix_Chunk* m_chunk = nullptr;
		std::string m_filepath;
		bool m_loaded = false;
		int m_channel = -1;
		int m_mapPos;
		Uint8 m_panLeft = 255;
		Uint8 m_panRight = 255;
		Uint8 m_volume = 128;
	};

	class Audio {
	public:
		void destroy(const bool& removeMap = false);

		void init(MIX_InitFlags flags);
		void init();
		Sound* loadSound(const std::string& filepath);

		void removeSound(Sound* sound, const bool& removeFromMap = false);
		void removeAllSounds();

		void removeElement(const int& ID);
		void removeUnloadedElements();
	private:
		std::map<int, Sound> m_sounds;
		bool m_init = false;
		int m_index = 0;
	};
}
