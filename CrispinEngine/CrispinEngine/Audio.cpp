#include "Audio.h"
#include "Statements.h"

#include <SDL2\SDL.h>

namespace Crispin {
	void Sound::remove() {
		Mix_FreeChunk(m_chunk);
	}

	void Sound::play(const int &loops) {
		// FIND CHANNEL TO PUT IT ON
		bool foundPlace = false;
		for (int i = 0; i < MIX_CHANNELS && !foundPlace; i++) {
			if (Mix_Playing(i) == 0) {
				m_channel = i;
				foundPlace = true;
			}
		}

		Mix_PlayChannel(m_channel, m_chunk, loops);
		Mix_SetPanning(m_channel, m_panLeft, m_panRight);
	}

	void Sound::setPan(const Uint8 &left, const Uint8 &right) {
		m_panLeft = left;
		m_panRight = right;
		Mix_SetPanning(m_channel, left, right);
	}

	Audio::Audio(MIX_InitFlags flags) {
		init(flags);
	}

	Audio::Audio() {
		// Empty
	}

	Audio::~Audio() {
		for (int i = 0; i < MIX_CHANNELS; i++) {
			Mix_HaltChannel(i);
		}
		for (auto& it : m_soundCache) {
			Mix_FreeChunk(it.second->m_chunk);
			it.second->m_chunk = NULL;
			delete &(it);
		}

		Mix_CloseAudio();
		Mix_Quit();
	}

	void Audio::init(MIX_InitFlags flags) {
		if (!m_initialized) {
			SDL_Init(SDL_INIT_AUDIO);
			if (Mix_Init(flags) == -1) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			init();
		}
		else {
			Warning("Sound engine cannot be initialized twice!");
		}
	}

	void Audio::init() {
		if (!m_initialized) {
			SDL_Init(SDL_INIT_AUDIO);
			if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY * 2, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			m_initialized = true;
		}
		else {
			Warning("Sound engine cannot be initialized twice!");
		}
	}

	// Load a sound effect by specifying the sounds location
	Sound Audio::loadSound(const std::string& filepath) {
		if (!m_initialized) {
			init();
		}

		Sound temp;

		// Check if temp exists in loaded cache
		auto it = m_soundCache.find(filepath.c_str());
		if (it == m_soundCache.end()) {
			// Failed to find sound
			temp.m_chunk = Mix_LoadWAV(filepath.c_str());
			if (!temp.m_chunk) {
				FatalError("Failed to load audio: " + std::string(Mix_GetError()));
			}

			m_soundCache[filepath] = &temp;
		}
		else {
			temp = *(it->second);
		}

		return temp;
	}
}