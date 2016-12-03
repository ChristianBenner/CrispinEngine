#include "Audio.h"
#include "..\Statements.h"

#include <SDL2\SDL.h>

namespace Crispin {
	void Sound::play(const int& loops) {
		if (m_loaded) {
			// FIND CHANNEL TO PUT IT ON
			bool foundPlace = false;
			for (int i = 0; i < MIX_CHANNELS && !foundPlace; i++) {
				if (Mix_Playing(i) == 0) {
					m_channel = i;
					Mix_SetPanning(m_channel, m_panLeft, m_panRight);
					foundPlace = true;
				}
			}

			if (!foundPlace) {
				// TODO: Make panning work somehow
				Warning("Could not find channel to play sound, panning will not work");
				m_channel = -1;
			}

			Mix_PlayChannel(m_channel, m_chunk, loops);
		}
		else {
			Warning("Sound not loaded, cannot play!");
		}
	}

	void Sound::setPan(const Uint8& left, const Uint8& right) {
		m_panLeft = left;
		m_panRight = right;
		Mix_SetPanning(m_channel, left, right);
	}

	AudioManager::AudioManager(){
		// Empty
	}

	AudioManager::~AudioManager() {
		destroy();
	}

	void AudioManager::destroy() {
		if (m_init) {
			m_init = false;

			Mix_HaltChannel(-1);
			for (auto it = m_sfxCache.begin(); it != m_sfxCache.end(); ++it) {
				Mix_FreeChunk(it->second);
				it->second = NULL;
			}

			m_sfxCache.clear();
			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	void AudioManager::init(MIX_InitFlags flags) {
		init();
		Mix_Init(flags);
	}

	void AudioManager::init() {
		if (!m_init) {
			SDL_Init(SDL_INIT_AUDIO);
			if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY * 2, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			m_init = true;
		}
		else {
			Warning("Sound engine cannot be initialized twice!");
		}
	}

	Sound AudioManager::loadSound(const std::string& filepath) {
		Sound effect;

		//Try to find audio in cache
		auto it = m_sfxCache.find(filepath);

		if (it == m_sfxCache.end()) {
			//failed to find - create new sfx
			Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());

			if (chunk == nullptr) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			//add sfx to cache
			m_sfxCache[filepath] = chunk;
			effect.m_chunk = chunk;
		}
		else {
			//cached already
			effect.m_chunk = it->second;
		}

		effect.m_filepath = filepath;
		effect.m_loaded = true;
		return effect;
	}

	void AudioManager::removeSound(Sound *sound) {
		if (sound->m_loaded) {
			auto it = m_sfxCache.find(sound->m_filepath);

			Mix_HaltChannel(sound->m_channel);
			Mix_FreeChunk(sound->m_chunk);
			sound->m_chunk = NULL;
			sound->m_loaded = false;

			m_sfxCache.at(sound->m_filepath) == nullptr;
			m_sfxCache.erase(sound->m_filepath);
		}
	}

	void AudioManager::removeSounds(std::map<int, Sound>* sounds) {
		for (auto it = sounds->begin(); it != sounds->end(); ++it) {
			removeSound(&(it->second));
		}
	}
}