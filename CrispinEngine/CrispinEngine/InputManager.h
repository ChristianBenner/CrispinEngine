/*
This is a user input management class developed for the 
Crispin Engine

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
#include <glm\glm.hpp>
#include <unordered_map>
namespace Crispin {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID),
			releaseKey(unsigned int keyID);

		bool isKeyDown(unsigned int keyID);

		//Returns true if key is just pressed
		bool isKeyPressed(unsigned int keyID);

		void setMousePos(float X, float Y);
		glm::vec2 getMousePos() const;
	private:
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mousePos;
	};
}