#pragma once
#include <GL/glew.h>
#include "../../Statements.h"

namespace Crispin {
	struct Position {
		float x, y;

		Position() {}
		Position(float X, float Y) {
			x = X;
			y = Y;
		}

		void setPosition(float X, float Y) {
			x = X;
			y = Y;
		}
	};

	struct ColorRGBA8 {
		//set default value to black (0)
		ColorRGBA8() : r(0), g(0), b(0), a(0) { }
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) { }

		GLubyte r, g, b, a;
	};

	struct UV { //texture scale co-ordinates
		float u;
		float v;

		void setUV(float U, float V) {
			u = U;
			v = V;
		}
	};

	struct Vertex {
		Position pos;
		ColorRGBA8 col = ColorRGBA8(255, 255, 255, 255);
		UV uv;

		void setPosition(float X, float Y) {
			pos.setPosition(X, Y);
		}

		void setUV(float U, float V) {
			uv.setUV(U, V);
		}

		void setPositionalData(float X, float Y, float U, float V) {
			pos.setPosition(X, Y);
			uv.setUV(U, V);
		}

		void setColour(const Crispin::ColorRGBA8& colour) {
			col = colour;
		}
	};

	class AbstractPiece {
	public:
		AbstractPiece() {}
		Position v1, v2, v3, v4;

		GLint textureID;
		int specificID;
	};

	class AbstractPieceColour {
	public:
		AbstractPieceColour() {}
		Vertex v1, v2, v3, v4;

		GLint textureID;
		int specificID;
	};
}