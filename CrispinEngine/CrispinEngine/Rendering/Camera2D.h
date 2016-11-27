/*
This is a camera class developed for the Crispin
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

March 26 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Crispin {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screen_width, int screen_height); //initialize camera with properties
		void update(); //update camera and matrix etc

		void setPosition(const glm::vec2 &position);
		void setScale(float scale);
		void move(float x, float y);

		bool isBoxInView(const glm::vec2& pos, const glm::vec2& dimensions);

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		glm::vec2 getPosition();
		glm::mat4 getCameraMatrix();
		float getScale();
	private:
		glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
		glm::mat4 m_cameraMatrix = glm::mat4(1.0f); //4x4 matrix
		 //store orphographic projection matrix
		glm::mat4 m_orthoMatrix = glm::mat4(1.0f);

		//scaling factor of graphics for zoom
		float m_scale = 1.0f;

		bool m_matrix_update_needed = true;
		
		int m_screen_width = 400;
		int m_screen_height = 400;
	};
}
