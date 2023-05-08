#pragma once
#include <GL/eglew.h>
#include "Vertex.h"

using namespace std;

class Sprite {
	//Atributos
	float x; //Posición x
	float y; //Posición y
	int width; //ancho del Sprite
	int height; //Alto del Sprite
	GLuint vboID; //(Objeto) Obtiene el ID de la variable creada por glew

//Métodos
public:
	//Constructor:
	Sprite();

	//Destructor:
	~Sprite();

	//Función para inicializar los elementos
	void Init(float x, float y, int width, int height);

	//Función para dibujar
	void draw();
};