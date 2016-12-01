#include "Audio.h"
#include "Statements.h"

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

	void Sound::setVolume(const Uint8& volume) {
		m_chunk->volume = volume;
		m_volume = volume;
	}

	void Sound::setPan(const Uint8& left, const Uint8& right) {
		m_panLeft = left;
		m_panRight = right;
		Mix_SetPanning(m_channel, left, right);
	}

	void Audio::init(MIX_InitFlags flags) {
		init();
		Mix_Init(flags);
	}

	void Audio::init() {
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

	void Audio::destroy(const bool& removeMap) {
		if (m_init) {
			m_init = false;

			removeAllSounds();

			if (removeMap) {
				m_sounds.clear();
			}

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	void Audio::removeElement(const int& ID) {
		m_sounds.erase(ID);
	}

	void Audio::removeUnloadedElements() {
		std::vector<int> elements;
		for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it) {
			if (!it->second.m_loaded) {
				// Add to list otherwise breaks iterator memory
				elements.push_back(it->first);
			}
		}

		for (int el : elements) {
			m_sounds.erase(el);
		}
		elements.clear();
	}
	
	Sound* Audio::loadSound(const std::string& filepath) {
		//Iterate through sounds to check if sound is already loaded
		int location = 0;
		for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it) {
			if (it->second.m_filepath.compare(filepath) == 0) {
				if (it->second.m_loaded) {
					// If the file is already in the cache and loaded
					return &(it->second);
				}

				// Load into location because filepath is the same but is not loaded (rare?)
				Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
				if (chunk == nullptr) {
					FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
				}

				m_sounds[location] = Sound();
				Sound* temp = &(m_sounds[location]);
				temp->m_chunk = chunk;
				temp->m_loaded = true;
				temp->m_filepath = filepath;
				temp->m_mapPos = location;
				return temp;
			}
			location++;
		}

		Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
		if (chunk == nullptr) {
			FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
		}

		m_sounds[m_index] = Sound();
		Sound* temp = &(m_sounds[m_index]);
		temp->m_chunk = chunk;
		temp->m_loaded = true;
		temp->m_filepath = filepath;
		temp->m_mapPos = m_index;
		m_index++;
		return temp;
	}

	void Audio::removeSound(Sound* sound, const bool& removeFromMap) {
		if (sound->m_loaded) {
			Mix_HaltChannel(sound->m_channel);
			Mix_FreeChunk(sound->m_chunk);
			sound->m_chunk = NULL;
			sound->m_loaded = false;

			if (removeFromMap) {
				m_sounds.erase(sound->m_mapPos);
			}
			// Sound remains in map :( - but chunk does not (not too bad if using audio engine per stage)
			printf("Removed: %s\n", sound->m_filepath.c_str());
		}
	}

	void Audio::removeAllSounds() {
		for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it) {
			removeSound(&(it->second));
		}
	}
}