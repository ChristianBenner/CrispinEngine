#include "Scene.h"
#include "Statements.h"

namespace Crispin {
	Scene::Scene()
	{
	}

	void Scene::draw() {

	}

	bool Scene::update(short* currentStage) {
		return true;
	}

	void Scene::destroy() {

	}

	void SceneManager::add(SceneData *sceneData) {
		m_scenes.push_back(sceneData);
	}

	bool SceneManager::run(short* currentSceneID) {
		bool useCurrent = false;
		if (m_currentScene != nullptr) {
			if (m_currentScene->p_ID == *currentSceneID) {
				// Awesome! We can run the scene without any drawback
				useCurrent = true;
			}
		}

		// Load new (if useCurrent = false)
		for (auto it = m_scenes.begin(); it != m_scenes.end() && !useCurrent; ++it) {
			if ((*it)->p_ID == *currentSceneID) {
				//Found
				useCurrent = true;
				m_currentScene = (*it);
			}
		}

		if (useCurrent) {
			// RUN! :D
			if (!m_currentScene->p_stage->update(currentSceneID)) {
				m_currentScene->p_stage->destroy();
				m_currentScene->p_stage = nullptr;
			}
			else {
				m_currentScene->p_stage->draw();
			}

			return true;
		}
		else {
			// An error has occured, the stage doesn't exist
			Crispin::Warning("The specified scene ID doesn't match any scenes in SceneManager");
			return false;
		}
	}
}