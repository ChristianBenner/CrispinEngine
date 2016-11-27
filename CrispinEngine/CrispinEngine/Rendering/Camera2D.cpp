#include "camera2D.h"
#include <iostream>

using namespace Crispin;
Camera2D::Camera2D(){ }

Camera2D::~Camera2D()
{
}

void Camera2D::init(int screen_width, int screen_height) {
	m_screen_width = screen_width;
	m_screen_height = screen_height;

	//build ortho matrix around screen properties
	m_orthoMatrix = glm::ortho(0.0f, (float)m_screen_width, 0.0f, (float)m_screen_height);
}

void Camera2D::update() {
	if (m_matrix_update_needed) {
		glm::vec3 translate(-m_position.x + m_screen_width / 2, -m_position.y + m_screen_height / 2, 0.0f);
		m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

		glm::vec3 scale(m_scale, m_scale, 0.0f);
		m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

		m_matrix_update_needed = false;
	}
}

void Camera2D::move(float x, float y) {
	m_position = m_position + glm::vec2(x, y);
}

void Camera2D::setPosition(const glm::vec2 &position) {
	m_position = position;
	m_matrix_update_needed = true;
}

glm::vec2 Camera2D::getPosition() {
	return m_position;
}

void Camera2D::setScale(float scale) {
	m_scale = scale;
	m_matrix_update_needed = true;
}

float Camera2D::getScale() {
	return m_scale;
}

glm::mat4 Camera2D::getCameraMatrix() {
	return m_cameraMatrix;
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
	//Invert Y
	screenCoords.y = m_screen_height - screenCoords.y;
	//Set 0 to center
	screenCoords -= glm::vec2(m_screen_width / 2, m_screen_height / 2);
	//Scale co-ordinates
	screenCoords /= m_scale;
	//Translate with cam position
	screenCoords += m_position;

	return screenCoords;
}

bool Camera2D::isBoxInView(const glm::vec2& pos, const glm::vec2& dimensions) {
	glm::vec2 scaledScreenDimensions = glm::vec2(m_screen_width, m_screen_height) / m_scale;

	// The minimum distance before a collision occurs
	const float MIN_DISTANCE_X = (dimensions.x / 2.0f) + (scaledScreenDimensions.x / 2.0f);
	const float MIN_DISTANCE_Y = (dimensions.y / 2.0f) + (scaledScreenDimensions.y / 2.0f);

	// Center position of objects
	glm::vec2 centerPos = pos + (dimensions / 2.0f);

	// Center position of camera center
	glm::vec2 centerCameraPos = m_position;

	// Vector from the object to the camera
	glm::vec2 distVec = centerPos - centerCameraPos;

	// Get the depth of the collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	// If either the depths are > 0, then we collided
	if (xDepth > 0 && yDepth > 0) {
		//There was a collision
		return true;
	}
	return false;
}