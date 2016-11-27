/*
This is an OpenGL rendering class developed for the Crispin
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

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace Crispin {

	// Determines how we should sort the glyphs
	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	// A glyph is a single quad. These are added via SpriteBatch::draw
	class Glyph {
	public:
		Glyph() {}

		Glyph(const glm::vec4& DestRect, const glm::vec4& UvRect, GLuint Texture, const float& Depth, const ColorRGBA8& Color, bool flip = false);

		Glyph(const glm::vec4& DestRect, const glm::vec4& UvRect, GLuint Texture, const float& Depth, const ColorRGBA8& Color, float angle, bool flip = false);

		Glyph(const AbstractPiece& dimensions, const glm::vec4& UvRect, const float& Depth, const ColorRGBA8& Color, bool flip = false);

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
		
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle);
	};

	// Each render batch is used for a single draw call
	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
			numVertices(NumVertices), texture(Texture) {
		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	// The SpriteBatch class is a more efficient way of drawing sprites
	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		// Initializes the spritebatch
		void init();

		// Begins the spritebatch
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		// Ends the spritebatch
		void end();

		// Adds a glyph to the spritebatch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, bool flip = false);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle, bool flip = false);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir, bool flip = false);

		void draw(const AbstractPiece& dimensions, const glm::vec4& uvRect, float depth, const ColorRGBA8& color, bool flip = false);

		// Renders the entire SpriteBatch to the screen
		void renderBatch();
	private:
		// Creates all the needed RenderBatches
		void createRenderBatches();

		// Generates our VAO and VBO
		void createVertexArray();

		// Sorts glyphs according to _sortType
		void sortGlyphs();

		// Comparators used by sortGlyphs()
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint m_vbo = 0;
		GLuint m_vao = 0;

		GlyphSortType m_sortType;

		std::vector<Glyph*> m_glyphPointers; //for sorting
		std::vector<Glyph> m_glyphs; //for storing
		std::vector<RenderBatch> m_renderBatches;
	};

}