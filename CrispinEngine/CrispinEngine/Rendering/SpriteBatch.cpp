#include "SpriteBatch.h"

#include <algorithm>

namespace Crispin {

	SpriteBatch::SpriteBatch() { }

	SpriteBatch::~SpriteBatch()
	{
	}


	void SpriteBatch::init() {
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */) {
		m_sortType = sortType;
		m_renderBatches.clear();

		// Delete any glyphs that remain so there's no memory leaks
		m_glyphs.clear();
	}

	void SpriteBatch::end() {
		// Reserve size
		m_glyphPointers.resize(m_glyphs.size());

		// Point all pointers to actual values
		for (int i = 0; i < m_glyphs.size(); i++) {
			m_glyphPointers[i] = &m_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	// Add to glyph (render data) array
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, bool flip) {
		///Glyph newGlyph; //allocating on stack
		//not anymore (optimization)
		///m_glyphs.push_back(newGlyph);

		//Much more simple and faster
		m_glyphs.emplace_back(Glyph(destRect, uvRect, texture, depth, color, flip));
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle, bool flip) {
		m_glyphs.emplace_back(Glyph(destRect, uvRect, texture, depth, color, angle, flip));
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir, bool flip) {
		// Convert direction to angle using glms dot product function
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, dir));
		if (dir.y < 0.0f) {
			angle = -angle;
		}

		m_glyphs.emplace_back(Glyph(destRect, uvRect, texture, depth, color, angle, flip));
	}

	void SpriteBatch::draw(const AbstractPiece& dimensions, const glm::vec4& uvRect, float depth, const ColorRGBA8& color, bool flip) {
		m_glyphs.emplace_back(Glyph(dimensions, uvRect, depth, color, flip));
	}

	void SpriteBatch::draw(const AbstractPieceColour& vertices, const glm::vec4& uvRect, float depth, bool flip) {
		m_glyphs.emplace_back(Glyph(vertices, uvRect, depth, flip));
	}

	void SpriteBatch::renderBatch() {

		// Bind array object. This sets up the opengl state, including the 
		// vertex attribute pointers and it binds the VBO
		glBindVertexArray(m_vao);

		for (int i = 0; i < m_renderBatches.size(); i++) {
			glActiveTexture(m_renderBatches[i].textureUnit);
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	// Upload glyphs to GPU
	void SpriteBatch::createRenderBatches() {
		// This will store all the vertices needed for upload
		std::vector <Vertex> vertices;
		// Resize the buffer to the exact size we need so we can treat
		// it like an array
		vertices.resize(m_glyphPointers.size() * 6);

		if (m_glyphPointers.empty()) {
			return;
		}

		int offset = 0; // current offset
		int cv = 0; // current vertex

		//Add the first batch
		m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->topRight;
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		offset += 6;

		//Add all the rest of the glyphs
		for (int cg = 1; cg < m_glyphPointers.size(); cg++) {
			// Check if this glyph can be part of the current batch
			if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture) {
				// Make a new batch
				m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
			}
			else {
				// If its part of the current batch, just increase numVertices
				m_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->topRight;
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			offset += 6;
		}

		// Bind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer (for speed)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray() {
		// Generate the VAO if it isn't already generated
		if (m_vao == 0) {
			glGenVertexArrays(1, &m_vao);
		}

		// Bind the VAO. All subsequent opengl calls will modify it's state.
		glBindVertexArray(m_vao);

		//G enerate the VBO if it isn't already generated
		if (m_vbo == 0) {
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

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

		glBindVertexArray(0);
	}

	// Default sort type is texture
	void SpriteBatch::sortGlyphs() {
		switch (m_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
		return (a->depth > b->depth);
	}

	/* Compare the position of two textures by ID - this is sorting
	all of the same textures next to eachover so the renderer doesn't have
	to switch textures much. */
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
		return (a->texture < b->texture);
	}

	glm::vec2 Glyph::rotatePoint(glm::vec2 pos, float angle) {
		glm::vec2 newV;
		newV.x = pos.x * cos(angle) - pos.y * sin(angle);
		newV.y = pos.x * sin(angle) + pos.y * cos(angle);

		return newV;
	}

	Glyph::Glyph(const glm::vec4& DestRect, const glm::vec4& UvRect, GLuint Texture, const float& Depth, const ColorRGBA8& Color, bool flip) :
		texture(Texture), depth(Depth){
		//here we can connect the vertex in the appropriate places for random map gen
		topLeft.col = Color;
		topLeft.setPosition(DestRect.x, DestRect.y + DestRect.w);

		bottomLeft.col = Color;
		bottomLeft.setPosition(DestRect.x, DestRect.y);

		bottomRight.col = Color;
		bottomRight.setPosition(DestRect.x + DestRect.z, DestRect.y);

		topRight.col = Color;
		topRight.setPosition(DestRect.x + DestRect.z, DestRect.y + DestRect.w);

		if (!flip) {
			topLeft.setUV(UvRect.x, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x, UvRect.y);
			bottomRight.setUV(UvRect.x + UvRect.z, UvRect.y);
			topRight.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
		}
		else {
			topLeft.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x + UvRect.z, UvRect.y);
			bottomRight.setUV(UvRect.x, UvRect.y);
			topRight.setUV(UvRect.x, UvRect.y + UvRect.w);
		}
	}

	Glyph::Glyph(const glm::vec4& DestRect, const glm::vec4& UvRect, GLuint Texture, const float& Depth, const ColorRGBA8& Color, float angle, bool flip) :
		texture(Texture), depth(Depth){
		glm::vec2 halfDims(DestRect.z / 2.0f, DestRect.w / 2.0f);

		//get vertices centered at origin
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		//rotate the points
		tl = rotatePoint(tl, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;
		

		//here we can connect the vertex in the appropriate places for random map gen
		topLeft.col = Color;
		topLeft.setPosition(DestRect.x + tl.x, DestRect.y + tl.y);

		bottomLeft.col = Color;
		bottomLeft.setPosition(DestRect.x + bl.x, DestRect.y + bl.y);

		bottomRight.col = Color;
		bottomRight.setPosition(DestRect.x + br.x, DestRect.y + br.y);

		topRight.col = Color;
		topRight.setPosition(DestRect.x + tr.x, DestRect.y + tr.y);

		if (!flip) {
			topLeft.setUV(UvRect.x, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x, UvRect.y);
			bottomRight.setUV(UvRect.x + UvRect.z, UvRect.y);
			topRight.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
		}
		else {
			topLeft.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x + UvRect.z, UvRect.y);
			bottomRight.setUV(UvRect.x, UvRect.y);
			topRight.setUV(UvRect.x, UvRect.y + UvRect.w);
		}
	}

	Glyph::Glyph(const AbstractPiece& dimensions, const glm::vec4& UvRect, const float& Depth, const ColorRGBA8& Color, bool flip)
		: texture(dimensions.textureID), depth(Depth) {
		topLeft.col = Color;
		topLeft.setPosition(dimensions.v1.x, dimensions.v1.y);

		bottomLeft.col = Color;
		bottomLeft.setPosition(dimensions.v2.x, dimensions.v2.y);

		bottomRight.col = Color;
		bottomRight.setPosition(dimensions.v3.x, dimensions.v3.y);

		topRight.col = Color;
		topRight.setPosition(dimensions.v4.x, dimensions.v4.y);

		if (!flip) {
			topLeft.setUV(UvRect.x, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x, UvRect.y);
			bottomRight.setUV(UvRect.x + UvRect.z, UvRect.y);
			topRight.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
		}
		else {
			topLeft.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x + UvRect.z, UvRect.y);
			bottomRight.setUV(UvRect.x, UvRect.y);
			topRight.setUV(UvRect.x, UvRect.y + UvRect.w);
		}
	}

	Glyph::Glyph(const AbstractPieceColour& vertices, const glm::vec4& UvRect, const float& Depth, bool flip)
		: texture(vertices.textureID), depth(Depth) {
		topLeft.col = vertices.v1.col;
		topLeft.setPosition(vertices.v1.pos.x, vertices.v1.pos.y);

		bottomLeft.col = vertices.v2.col;
		bottomLeft.setPosition(vertices.v2.pos.x, vertices.v2.pos.y);

		bottomRight.col = vertices.v3.col;
		bottomRight.setPosition(vertices.v3.pos.x, vertices.v3.pos.y);

		topRight.col = vertices.v4.col;
		topRight.setPosition(vertices.v4.pos.x, vertices.v4.pos.y);

		if (!flip) {
			topLeft.setUV(UvRect.x, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x, UvRect.y);
			bottomRight.setUV(UvRect.x + UvRect.z, UvRect.y);
			topRight.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
		}
		else {
			topLeft.setUV(UvRect.x + UvRect.z, UvRect.y + UvRect.w);
			bottomLeft.setUV(UvRect.x + UvRect.z, UvRect.y);
			bottomRight.setUV(UvRect.x, UvRect.y);
			topRight.setUV(UvRect.x, UvRect.y + UvRect.w);
		}
	}
}