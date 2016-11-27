/*
These are audio playback classes (sound effect, music and
sound engine) developed for the Crispin Engine

Use it for any of your projects, commercial or otherwise,
free of charge, but do not remove this disclaimer.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

March 26 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

#pragma once

#ifndef AudioEngine_h__
#define AudioEngine_h__

#include <SDL2/SDL_mixer.h>
#include "../Statements.h"
#include <string>
#include <map>

namespace Crispin {
	class SoundEffect {
	public:
		//nobody can use private variables except friend class
		friend class AudioEngine;

		void play(int loops = 0);
	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	// Currently broken
	class Music {
	public:
		friend class AudioEngine;

		//If loops == -1, loop forever, otherwise play loops times
		void play(int loops = 1);

		//Control music (only once can play at a time)
		static void pause();
		static void resume();
		static void stop();
		static void setVolume(int volume);
	private:
		Mix_Music* m_music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy(); //clean up

		//load to or get from cache
		SoundEffect loadSoundEffect(const std::string& filePath);
		void removeSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);
	private:
		bool m_isInitialized = false;

		//Sound effect cache
		std::map<std::string, Mix_Chunk*> m_sfxCache;

		//Music cache
		std::map<std::string, Mix_Music*> m_musicCache;
	};

}

#endif AudioEngine_h__