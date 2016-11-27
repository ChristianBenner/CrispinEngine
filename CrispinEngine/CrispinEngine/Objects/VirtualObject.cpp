#include "VirtualObject.h"

namespace Crispin {
	VirtualObject::VirtualObject()
	{
	}

	VirtualObject::~VirtualObject()
	{
		m_vertices.clear();
	}

	void VirtualObject::setVertices(std::vector<glm::vec2> vertices) {
		m_vertices.clear();
		m_vertices = vertices;
	}

	void VirtualObject::addVertex(const glm::vec2& Vertex) {
		m_vertices.emplace_back(Vertex);
	}

	std::vector<glm::vec2>* VirtualObject::getVertices() {
		return &m_vertices;
	}

	void VirtualObject::setDirection(const glm::vec2& direction) {
		m_direction = direction;
	}

	glm::vec2 VirtualObject::getDirection() {
		return m_direction;
	}

	void VirtualObject::setSpeed(const float& speed) {
		m_speed = speed;
	}

	float VirtualObject::getSpeed() {
		return m_speed;
	}

	void VirtualObject::setColour(const ColorRGBA8& colour) {
		m_colour = colour;
	}

	ColorRGBA8 VirtualObject::getColour() {
		return m_colour;
	}

	void VirtualObject::setTexture(GLint textureID) {
		m_textureID = textureID;
	}
};