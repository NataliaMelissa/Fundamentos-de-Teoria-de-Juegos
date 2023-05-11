#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>


//Método: Constructor:
Sprite::Sprite() {
	vboID = 0;
}

//Método: Destructor:
Sprite::~Sprite() {

	if (vboID != 0) { 
		glDeleteBuffers(1, &vboID); //Borrar el buffer del ID
	}
}

//Método: Función para inicializar los elementos
void Sprite::Init(float x, float y, int width, int height, string TexturePath) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	//Si no hay ningún objeto glew creado
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	/*float VertexData[12]; //Vector que contiene todos los vértices del sprite

	//Inicializar los vértices del vector VertexData:
	//Coordenadas vértice 1
	VertexData[0] = x + width;
	VertexData[1] = y + height;

	//Coordenadas vértice 2
	VertexData[2] = x;
	VertexData[3] = y + height;

	//Coordenadas vértice 3
	VertexData[4] = x;
	VertexData[5] = y;

	//Coordenadas vértice 4
	VertexData[6] = x;
	VertexData[7] = y;

	//Coordenadas vértice 5
	VertexData[8] = x + width;
	VertexData[9] = y;

	//Coordenadas vértice 6
	VertexData[10] = x + width;
	VertexData[11] = y + height;*/

	texture = ResourceManager::getTexture(TexturePath); //Asignar la imágen a la textura

	Vertex VertexData[6]; //Variable con los vectores de las posiciones de los vértices

	//Inicializar las posiciones UV de la imágen del sprite para cada vértice:
	VertexData[0].SetUV(1.0f, 1.0f); //Vértice 1
	VertexData[1].SetUV(0.0f, 1.0f); //Vértice 2
	VertexData[2].SetUV(0.0f, 0.0f); //Vértice 3
	VertexData[3].SetUV(0.0f, 0.0f); //Vértice 4
	VertexData[4].SetUV(1.0f, 0.0f); //Vértice 5
	VertexData[5].SetUV(1.0f, 1.0f); //Vértice 6


	//Inicializar las posiciones de los vértices
	VertexData[0].SetPosition(x + width, y + height);	//Vértice 1
	VertexData[1].SetPosition(x, y + height);			//Vértice 2
	VertexData[2].SetPosition(x, y);					//Vértice 3 
	VertexData[3].SetPosition(x, y);					//Vértice 4
	VertexData[4].SetPosition(x + width, y);			//Vértice 5
	VertexData[5].SetPosition(x + width, y + height);	//Vértice 6

	//Inicializar el color de los vértices:
	for (int i = 0; i < 6; i++) {
		VertexData[i].SetColor(255, 255, 0, 255);
	}

	VertexData[1].SetColor(255, 0, 255, 255); //Cambiar color del Vértice 2
	VertexData[4].SetColor(0, 0, 255, 255); //Cambiar color del Vértice 5

	//Pasar la información de los vértices al buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboID); //Función para mandarle la información del buffer de arrays
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW); //Funcipon para mandarle la información al buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Función para liberar la memoria de todo lo asignado
}

//Método: Función para dibujar
void Sprite::draw() {
	glBindTexture(GL_TEXTURE_2D, texture.id); //1.1 Mandar el ID de la texturav
	glBindBuffer(GL_ARRAY_BUFFER, vboID); //1.2 Pasar la información al buffer

	//Pasar la información de Posición
	glEnableVertexAttribArray(0); //2. Recibe la información de la posición
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //3. Mandar información de todos los vértices al buffer

	//Pasar la información de Color
	//glEnableVertexAttribArray(1); //Recibe que se le pasa otro atributo (atributo de color)
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); //Recibe la información de color del vértice
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)); //Recibe la información de las coordenadas uv del vértice

	glDrawArrays(GL_TRIANGLES, 0, 6); //Función para dibujar
	glDisableVertexAttribArray(0); //Decirle que ya no va a recibir información
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Limpiar los datos enviados


}