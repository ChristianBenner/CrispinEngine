/*
These are audio playback classes (sound, music and
audio manager) developed for the Crispin Engine

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

Created: March 26 2016
Edited: December 03 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

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

		void pause();
		void resume();
		void stop();

		Uint8 getPanLeft() { return m_panLeft; }
		Uint8 getPanRight() { return m_panRight; }
		Uint8 getVolume() { return m_volume; }
		bool isPaused() { return m_paused; }
		bool isLoaded() { return m_loaded; }
		std::string getFilePath() { return m_filepath; }
	private:
		Mix_Chunk* m_chunk = nullptr;
		std::string m_filepath;
		int m_channel = -1;
		bool m_loaded = false;
		bool m_paused = false;
		Uint8 m_panLeft = 255;
		Uint8 m_panRight = 255;
		Uint8 m_volume = 128;
	};

	class Music {
	public:
		friend class AudioManager;

		void play(const int& loops = 1);
		void fadeIn(const int& msTime, const int& loops = 1);
		void fadeOut(const int& msTime);

		void pause();
		void resume();
		void stop();
		void setVolume(const Uint8& volume);

		Uint8 getVolume() { return m_volume; }
		bool isPaused() { return m_paused; }
		bool isLoaded() { return m_loaded; }
		std::string getFilePath() { return m_filepath; }
		int isPlaying() { return Mix_PlayingMusic(); }
	private:
		Mix_Music* m_music = nullptr;
		std::string m_filepath;
		Uint8 m_volume = 128;
		bool m_loaded = false;
		bool m_paused = false;
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
		Music loadMusic(const std::string& filepath);

		void removeSound(Sound* sound);
		void removeSounds(std::map<int, Sound>* sounds);
		void removeMusic(Music* music);
	private:
		// Sound cache
		std::map<std::string, Mix_Chunk*> m_chunkCache;

		// Music cache
		std::map<std::string, Mix_Music*> m_musicCache;

		bool m_init = false;
	};
}
