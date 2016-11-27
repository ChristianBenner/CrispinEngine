#include "InputManager.h"
#include <SDL2\SDL.h>

namespace Crispin {

	InputManager::InputManager() : m_mousePos(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update() {
		//copy used keymap to new keymap - does same as below
		for (auto& it : m_keyMap) {
			m_previousKeyMap[it.first] = it.second;
		}
		/*//Old method < cpp11
		for (auto it = m_keyMap.begin(); it != m_keyMap.end(); ++it) {
			m_previousKeyMap[it->first] = it->second;
		}*/
	}

	void InputManager::pressKey(unsigned int keyID) {
		m_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		m_keyMap[keyID] = false;
	}

	bool InputManager::isKeyDown(unsigned int keyID) {
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	bool InputManager::wasKeyDown(unsigned int keyID) {
		auto it = m_previousKeyMap.find(keyID);
		if (it != m_previousKeyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		//check if was pressed this frame but not held down last frame
		if (isKeyDown(keyID) && !wasKeyDown(keyID)) {
			return true;
		}
		return false;
	}

	void InputManager::setMousePos(float X, float Y) {
		m_mousePos.x = X;
		m_mousePos.y = Y;
	}

	glm::vec2 InputManager::getMousePos() const {
		return m_mousePos;
	}
}