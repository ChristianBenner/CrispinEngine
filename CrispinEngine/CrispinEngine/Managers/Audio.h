#pragma once
#include <string>
#include <map>
#include <vector>

#include <SDL2/SDL_mixer.h>

namespace Crispin {
	// Manage sound data. Use Audio class to load
	class Sound {
	public:
		friend class AudioManager;

		void play(const int& loops = 0);

		void setPan(const Uint8& left, const Uint8& right);
		void setVolume(const Uint8& volume);

		Uint8 getPanLeft() { return m_panLeft; }
		Uint8 getPanRight() { return m_panRight; }
	private:
		Mix_Chunk* m_chunk = nullptr;
		std::string m_filepath;
		int m_channel = -1;
		bool m_loaded = false;
		Uint8 m_panLeft = 255;
		Uint8 m_panRight = 255;
		Uint8 m_volume = 128;
	};

	// Sound manager
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		void destroy();

		void init(MIX_InitFlags flags);
		void init();

		Sound loadSound(const std::string& filepath);

		void removeSound(Sound* sound);
		void removeSounds(std::map<int, Sound>* sounds);
	private:
		std::map<std::string, Mix_Chunk*> m_sfxCache;
		bool m_init = false;
	};
}
