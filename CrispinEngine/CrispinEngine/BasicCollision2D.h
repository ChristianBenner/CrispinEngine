/*
This is a collision detection class developed for the Crispin
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

April 19 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

#pragma once

#ifndef BasicCollision_h__
#define BasicCollision_h__

#include "VirtualObject.h"

#include <tuple>

namespace Crispin {
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	typedef std::tuple<bool, Direction, glm::vec2> Collision;

	extern Collision rectangleCollision(const glm::vec4& obj1, const glm::vec4& obj2);
	extern Collision rectangleOuterCollision(const glm::vec4& obj1, const glm::vec4& borders);
	extern Collision ballToRectangleCollision(const glm::vec2& ball, const float& radius, const glm::vec4& rectangle);
}

#endif