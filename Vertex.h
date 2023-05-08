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

struct Vertex {
	Position position; //Posición del vértice
	Color color; //Color del vértice

	void SetPosition(float _x, float _y) {
		position.SetXY(_x, _y);
	}

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.SetColors(r, g, b, a);
	}
};