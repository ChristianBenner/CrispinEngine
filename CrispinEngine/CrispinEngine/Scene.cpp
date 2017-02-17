#include "Scene.h"
#include "Statements.h"

namespace Crispin {
	Scene::Scene()
	{
	}

	void Scene::draw() {

	}

	bool Scene::update() {
		return true;
	}

	void Scene::destroy() {

	}

	void SceneManager::setStage(const int& sceneID) {
		m_currentID = sceneID;
	}

	void SceneManager::add(SceneData *sceneData) {
		m_scenes.push_back(sceneData);
	}

	bool SceneManager::run() {
		if (m_currentID == -1) {
			return false;
		}

		bool useCurrent = false;
		if (m_currentScene != nullptr) {
			if (m_currentScene->p_ID == m_currentID) {
				// Awesome! We can run the scene without any drawback
				useCurrent = true;
			}
		}

		// Load new (if useCurrent = false)
		for (auto it = m_scenes.begin(); it != m_scenes.end() && !useCurrent; ++it) {
			if ((*it)->p_ID == m_currentID) {
				//Found
				useCurrent = true;
				m_currentScene = (*it);
			}
		}

		if (useCurrent) {
			// RUN! :D
			if (!m_currentScene->p_stage->update()) {
				m_currentID = m_currentScene->getNextStage();
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

		// Run overlay scene e.g. options pane
		if (m_overlayScene != nullptr) {
			if (!m_overlayScene->p_stage->update()) {
				m_overlayScene->p_stage->destroy();
				m_overlayScene->p_stage = nullptr;
			}
			else {
				m_overlayScene->p_stage->draw();
			}
		}
	}

	void SceneManager::setOverlay(SceneData *sceneData) {
		m_overlayScene = sceneData;
	}
}