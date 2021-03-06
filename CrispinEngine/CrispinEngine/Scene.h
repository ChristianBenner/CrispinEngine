/*
This is the scene managing class developed for the Crispin
Engine

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

Created: December 03 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

/// TODO: ADD A SEPERATE 'OVERLAY' SCENE - Works same way and when not in use = nullptr
#pragma once
#include <map>
#include "Managers\Audio.h"
#include "Objects\Data\GLTexture.h"

namespace Crispin {
	class Scene
	{
	public:
		friend class SceneManager;

		Scene();

		virtual void draw() = 0;
		virtual bool update() = 0;
		virtual void destroy() = 0;

		int p_nextStage = -1;
	};

	class SceneData {
	public:
		SceneData(Scene* stage, int ID, int nextStage = -1) {
			p_stage = stage;
			p_ID = ID;
			p_stage->p_nextStage = nextStage;
		}

		int getNextStage() { return p_stage->p_nextStage; }

		Scene* p_stage;
		int p_ID;
	};

	class SceneManager {
	public:
		// Set the current stage
		void setStage(const int& sceneID);

		// Add a scene to the list of scenes
		void add(SceneData *sceneData);

		// Run a specified scene - returns successful boolean
		bool run();

		// Do not specify a scene if want to clear overlay
		void setOverlay(SceneData *sceneData = nullptr);
	private:
		SceneData* m_currentScene = nullptr;
		SceneData* m_overlayScene = nullptr;
		std::vector<SceneData*> m_scenes;

		int m_currentID = 0;
	};
}