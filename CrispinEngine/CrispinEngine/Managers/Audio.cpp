#include "Audio.h"
#include "..\Statements.h"

#include <SDL2\SDL.h>

#pragma once

#ifndef Audio_h__
#define Audio_h__

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
		Mix_VolumeChunk(m_chunk, volume);
		m_volume = volume;
	}

	void Sound::setPan(const Uint8& left, const Uint8& right) {
		m_panLeft = left;
		m_panRight = right;
		Mix_SetPanning(m_channel, left, right);
	}

	void Sound::pause() {
		Mix_Pause(m_channel);
		m_paused = true;
	}

	void Sound::resume() {
		Mix_Resume(m_channel);
		m_paused = false;
	}

	void Sound::stop() {
		Mix_HaltChannel(m_channel);
		m_paused = true;
	}

	void Music::play(const int& loops) {
		if (m_loaded) {
			if (Mix_PlayMusic(m_music, loops) == -1) {
				FatalError("SDL Music error: " + std::string(Mix_GetError()));
			}
		}
	}

	void Music::setVolume(const Uint8& volume) {
		Mix_VolumeMusic(volume);
		m_volume = volume;
	}

	void Music::pause() {
		Mix_PauseMusic();
		m_paused = true;
	}

	void Music::resume() {
		Mix_ResumeMusic();
		m_paused = false;
	}

	void Music::stop() {
		Mix_HaltMusic();
		m_paused = true;
	}

	void Music::fadeIn(const int& msTime, const int& loops) {
		if (Mix_FadeInMusic(m_music, loops, msTime) == -1) {
			Warning("SDL Mixer error: " + std::string(Mix_GetError()));
		}
	}

	void Music::fadeOut(const int& msTime) {
		Mix_FadeOutMusic(msTime);
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
			for (auto it = m_chunkCache.begin(); it != m_chunkCache.end(); ++it) {
				Mix_FreeChunk(it->second);
				it->second = NULL;
			}
			
			Mix_HaltMusic();
			for (auto it = m_musicCache.begin(); it != m_musicCache.end(); ++it) {
				Mix_FreeMusic(it->second);
				it->second = NULL;
			}

			m_chunkCache.clear();
			m_musicCache.clear();
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
		auto it = m_chunkCache.find(filepath);

		if (it == m_chunkCache.end()) {
			//failed to find - create new sfx
			Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());

			if (chunk == nullptr) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			//add sfx to cache
			m_chunkCache[filepath] = chunk;
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

	Music AudioManager::loadMusic(const std::string& filepath) {
		Music music;

		auto it = m_musicCache.find(filepath);
		if (it == m_musicCache.end()) {
			Mix_Music* mixMusic = Mix_LoadMUS(filepath.c_str());

			if (mixMusic == nullptr) {
				FatalError("SDL Mixer error: " + std::string(Mix_GetError()));
			}

			m_musicCache[filepath] = mixMusic;
			music.m_music = mixMusic;
		}
		else {
			music.m_music = it->second;
		}

		music.m_filepath = filepath;
		music.m_loaded = true;
		return music;
	}

	void AudioManager::removeSound(Sound *sound) {
		if (sound->m_loaded) {
			Mix_HaltChannel(sound->m_channel);
			Mix_FreeChunk(sound->m_chunk);
			sound->m_chunk = NULL;
			sound->m_loaded = false;

			m_chunkCache.at(sound->m_filepath) == nullptr;
			m_chunkCache.erase(sound->m_filepath);
		}
		else {
			Warning("Cannot remove sound that isn't loaded: "
				+ std::string(sound->m_filepath.c_str()));
		}
	}

	void AudioManager::removeSounds(std::map<int, Sound>* sounds) {
		for (auto it = sounds->begin(); it != sounds->end(); ++it) {
			removeSound(&(it->second));
		}
	}

	void AudioManager::removeMusic(Music *music) {
		if (music->m_loaded) {
			Mix_HaltMusic();
			Mix_FreeMusic(music->m_music);
			music->m_loaded = false;
			music->m_music = NULL;

			m_musicCache.at(music->m_filepath) == nullptr;
			m_musicCache.erase(music->m_filepath);
		}else{
			Warning("Cannot remove music that isn't loaded: " 
				+ std::string(music->m_filepath.c_str()));
		}
	}
}

#endif Audio_h__