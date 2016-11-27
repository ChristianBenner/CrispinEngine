#include "ObjectRectangle.h"
#include "../Loading/Resource.h"

namespace Crispin {
	ObjectRectangle::ObjectRectangle()
	{
	}


	ObjectRectangle::~ObjectRectangle()
	{
	}

	void ObjectRectangle::setDimensions(const glm::vec2& position,
		const glm::vec2& size) {
		m_vertices.emplace_back(position);
		m_vertices.emplace_back(size);
	}

	void ObjectRectangle::update(const float& deltaTime) {
		m_vertices[0] += m_direction * m_speed;
	}

	void ObjectRectangle::draw(SpriteBatch& renderBatch) {
		glm::vec4 textureUVMap(0.0f, 0.0f, 1.0f, 1.0f);
		renderBatch.draw(glm::vec4(m_vertices.at(0), m_vertices.at(1)), textureUVMap,
			m_textureID, 1.0f, m_colour, m_direction);
	}
}