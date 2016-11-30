#pragma once
#include <string>
#include <map>
#include <vector>

#include <SDL2/SDL_mixer.h>

namespace Crispin {
	class Sound {
	public:
		friend class Audio;

		void play(const int& loops);
		void remove();
		void setPan(const Uint8 &left, const Uint8 &right);

		Uint8 getLeftPan() {
			return m_panLeft;
		}

		Uint8 getRightPan() {
			return m_panRight;
		}
	private:
		// The same chunk can play on more than one channel
		std::vector<int> m_channels;// What channels is this same chunk playing on
		int m_channel = -1; // What channel is it on
		//float volume = 255.0f;

		Uint8 m_panLeft = 255;
		Uint8 m_panRight = 255;

		bool m_autoDestroy = true;

		Mix_Chunk* m_chunk;
	};

	class Music {
	public:
		friend class Audio;

	private:

	};

	class Audio
	{
	public:
		Audio(MIX_InitFlags flags);
		Audio();
		~Audio();

		void init(MIX_InitFlags flags);
		void init();

		//Play function - if not loaded/in map then load
		Sound loadSound(const std::string& filepath);

	private:
		bool m_initialized = false;

		std::map<std::string, Sound*> m_soundCache;
		//std::map<std::string, Mix_Music*> m_musicCache;
	};
}
