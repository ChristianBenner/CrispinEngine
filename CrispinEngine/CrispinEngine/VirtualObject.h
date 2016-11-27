/*
This is a virtual object parent class developed for the 
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

April 18 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

#ifndef VirtualObject_h__
#define VirtualObject_h__

#include <vector>
#include <glm/glm.hpp>

#include "Vertex.h"

/*The virtual object will be the parent class to all objects
used in a game. It will have vector of vec2s for positional
data that will be interpreted and used by subclasses for
usage.

For example a circle may only push back one vec2 for its
position, but a rectangle may push back two vec2's for its
top left position and bottom right*/
namespace Crispin {
	class VirtualObject{
	public:
		VirtualObject();
		~VirtualObject();

		void update(const float& deltaTime) {
			// empty
		}

		// Setters and getters
		void setVertices(std::vector<glm::vec2> vertices);
		void addVertex(const glm::vec2& Vertex);
		std::vector<glm::vec2>* getVertices();

		void setDirection(const glm::vec2& direction);
		glm::vec2 getDirection();

		void setSpeed(const float& speed);
		float getSpeed();

		void setColour(const ColorRGBA8& colour);
		ColorRGBA8 getColour();

		void setTexture(GLint textureID);

	protected:
		// Positional data
		std::vector<glm::vec2> m_vertices;

		// Movement data
		glm::vec2 m_direction;
		float m_speed;

		// Other
		ColorRGBA8 m_colour;
		GLint m_textureID;
	};
}
#endif