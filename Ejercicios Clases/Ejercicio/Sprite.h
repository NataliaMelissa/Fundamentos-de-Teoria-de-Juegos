#pragma once
#include <GL/eglew.h>
#include "Vertex.h"
#include "GLTexture.h"
#include <string>

using namespace std;

class Sprite {
	//Atributos
	float x; //Posición x
	float y; //Posición y
	int width; //ancho del Sprite
	int height; //Alto del Sprite
	GLuint vboID; //(Objeto) Obtiene el ID de la variable creada por glew
	GLTexture texture; //Textura

	//Métodos
public:
	//Constructor:
	Sprite();

	//Destructor:
	~Sprite();

	//Función para inicializar los elementos
	void Init(float x, float y, int width, int height, string TexturePath);

	//Función para dibujar
	void draw();
};