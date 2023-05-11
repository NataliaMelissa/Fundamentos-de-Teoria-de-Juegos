#pragma once
#include <GL/eglew.h>

struct Position {
	float x;
	float y;

	void SetXY(float _x, float _y) {
		x = _x;
		y = _y;
	}
};

struct Color {
	GLubyte r; //r = red
	GLubyte g; //g = green
	GLubyte b; //b = blue
	GLubyte a; //a = alpha = transparencia

	void SetColors(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

struct UV {
	float u; //Coordenada u (plano im�genes)
	float v; //Coordenada v (plano im�genes)

	void set(float u, float v) {
		this->u = u;
		this->v = v;
	}
};

struct Vertex {
	Position position; //Posici�n del v�rtice
	Color color; //Color del v�rtice
	UV uv; //Posici�n uv del v�rtice (im�gen)

	void SetPosition(float _x, float _y) {
		position.SetXY(_x, _y);
	}

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.SetColors(r, g, b, a);
	}

	void SetUV(float u, float v) {
		uv.set(u, v);
	}
};