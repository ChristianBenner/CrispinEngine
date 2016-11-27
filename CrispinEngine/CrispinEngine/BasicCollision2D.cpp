#include "BasicCollision2D.h"

namespace Crispin {
	Direction VectorDirection(const glm::vec2& target) {
		glm::vec2 compass[] = {
			glm::vec2(0.0f, 1.0f),  //up
			glm::vec2(1.0f, 0.0f),  //right
			glm::vec2(0.0f, -1.0f), //down
			glm::vec2(-1.0f, 0.0f)  //left
		};
		float max = 0.0f;
		unsigned int bestMatch = -1;

		for (unsigned int i = 0; i < 4; i++) {
			float dotProduct = glm::dot(glm::normalize(target), compass[i]);
			if (dotProduct > max) {
				max = dotProduct;
				bestMatch = i;
			}
		}

		return (Direction)bestMatch;
	}

	Collision rectangleCollision(const glm::vec4& obj1, const glm::vec4& obj2) {
		bool xCollision = obj1.x + obj1.z >= obj2.x &&
			obj2.x + obj2.z >= obj1.x;

		bool yCollision = obj1.y + obj1.w >= obj2.y &&
			obj2.y + obj2.w >= obj1.y;

		//work on
		glm::vec2 difference = glm::vec2(obj2.x, obj2.y)
			- glm::vec2(obj1.x, obj1.y);

		if (xCollision && yCollision) {
			return std::make_tuple(true, VectorDirection(difference), difference);
		}else{
			return std::make_tuple(false, UP, glm::vec2(0, 0));
		}
	}

	/* Check if an object is outside of a border, if so then return collision true
	and which border passed e.g. up, down, left, right. Also return how far into the
	border the object collided for repositioning */
	Collision rectangleOuterCollision(const glm::vec4& obj1, const glm::vec4& borders) {
		// Return different values for collisions with each side
		if (obj1.x <= borders.x) {
			float differenceX = obj1.x - borders.x;
			return std::make_tuple(true, LEFT, glm::vec2(differenceX, 0.0f));
		}
		if (obj1.x + obj1.z >= borders.x + borders.z) {
			float differenceX = (obj1.x + obj1.z) - (borders.x + borders.z);
			return std::make_tuple(true, RIGHT, glm::vec2(differenceX, 0.0f));
		}
		if (obj1.y <= borders.y) {
			float differenceY = obj1.y - borders.y;
			return std::make_tuple(true, DOWN, glm::vec2(0.0f, differenceY));
		}
		if (obj1.y + obj1.w >= borders.y + borders.w) {
			float differenceY = (obj1.y + obj1.w) - (borders.y + borders.w);
			return std::make_tuple(true, UP, glm::vec2(0.0f, differenceY));
		}else {
			return std::make_tuple(false, UP, glm::vec2(0, 0));
		}
	}
}