#pragma once
#include <GL/eglew.h>
#include "Vertex.h"
#include "GLTexture.h"
#include <string>

using namespace std;

class Sprite {
	//Atributos
	float x; //Posici�n x
	float y; //Posici�n y
	int width; //ancho del Sprite
	int height; //Alto del Sprite
	GLuint vboID; //(Objeto) Obtiene el ID de la variable creada por glew
	GLTexture texture; //Textura

	//M�todos
public:
	//Constructor:
	Sprite();

	//Destructor:
	~Sprite();

	//Funci�n para inicializar los elementos
	void Init(float x, float y, int width, int height, string TexturePath);

	//Funci�n para dibujar
	void draw();
};