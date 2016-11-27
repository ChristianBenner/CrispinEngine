#include "Sprite.h"
#include "../Objects/Data/Vertex.h"
#include "../Loading/Resource.h"

#include <cstddef>

namespace Crispin {

	Sprite::Sprite()
	{
		m_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (m_vboID != 0) {
			glDeleteBuffers(1, &m_vboID);
		}
	}

	//Initializes the sprite VBO. x, y, width, and height are
	//in the normalized device coordinate space. so, [-1, 1]
	void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;

		m_texture = Resource::getTexture(texturePath);

		//Generate the buffer if it hasn't already been generated
		if (m_vboID == 0) {
			glGenBuffers(1, &m_vboID);
		}

		// Hold vertex data for two triangles (make a rectangle)
		Vertex vertexData[6];

		//First Triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		//Set all vertex colors to magenta
		for (int i = 0; i < 6; i++) {
			vertexData[4].col = ColorRGBA8(255, 0, 255, 255);
		}
		vertexData[4].col = ColorRGBA8(0, 0, 255, 255);
		vertexData[4].col = ColorRGBA8(0, 255, 0, 255);


		//Tell opengl to bind vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		//Upload the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		//Unbind the buffer (optional)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//Draws the sprite to the screen
	void Sprite::draw() {

		glBindTexture(GL_TEXTURE_2D, m_texture.ID);
		//glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_texture.width, m_texture.height, GL_TRUE);
		//glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_texture.ID, 0);

		//bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		//Tell opengl what attribute arrays we need
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//Draw the 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Disable the vertex attrib arrays. This is not optional.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}