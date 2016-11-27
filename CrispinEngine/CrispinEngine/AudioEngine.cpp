#include "AudioEngine.h"

namespace Crispin {
	void SoundEffect::play(int loops) {
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
			FatalError("SDL SFX error: " + std::string(Mix_GetError()));
		}
	}

	void Music::play(int loops) {
		if (Mix_PlayMusic(m_music, loops) == -1) {
			FatalError("SDL Music error: " + std::string(Mix_GetError()));
		}
	}

	void Music::setVolume(int volume) {
		Mix_VolumeMusic(volume);
	}

	void Music::pause() {
		Mix_PausedMusic();
	}

	void Music::resume() {
		Mix_ResumeMusic();
	}

	void Music::stop() {
		Mix_HaltMusic();
	}

	AudioEngine::AudioEngine()
	{
		// Empty
	}

	AudioEngine::~AudioEngine()
	{
		destroy();
	}

	void AudioEngine::init() {
		if (m_isInitialized) {
			FatalError("Sound engine initialized twice!");
		}
		/* initialize mixer
			MIX_INIT_FAC
			MIX_INIT_MP3
			MIX_INIT_MOD
			MIX_INIT_OGG
		*/
		//if failed
		if (Mix_Init(MIX_INIT_OGG) == -1) {
			FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY * 2, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
		}

		m_isInitialized = true;
	}

	void AudioEngine::destroy() {
		if (m_isInitialized) {
			m_isInitialized = false;
			
			//iterate through the caches
			for (auto& it : m_sfxCache) {
				Mix_FreeChunk(it.second);
			}
			for (auto& it : m_musicCache) {
				Mix_FreeMusic(it.second);
			}
			m_sfxCache.clear();
			m_musicCache.clear();

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
		SoundEffect effect;

		//Try to find audio in cache
		auto it = m_sfxCache.find(filePath);

		if (it == m_sfxCache.end()) {
			//failed to find - create new sfx
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			
			if (chunk == nullptr) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			//add sfx to cache
			m_sfxCache[filePath] = chunk;
			effect.m_chunk = chunk;
		}
		else {
			//cached already
			effect.m_chunk = it->second;
		}

		return effect;
	}

	Music AudioEngine::loadMusic(const std::string& filePath) {
		Music music;

		auto it = m_musicCache.find(filePath);
		if (it == m_musicCache.end()) {
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());

			if (mixMusic == nullptr) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			m_musicCache[filePath] = mixMusic;
			music.m_music = mixMusic;
		}
		else {
			music.m_music = it->second;
		}

		return music;
	}

	void AudioEngine::removeSoundEffect(const std::string& filePath) {
		m_sfxCache.at(filePath) == nullptr;
		m_sfxCache.erase(filePath);
	}
}