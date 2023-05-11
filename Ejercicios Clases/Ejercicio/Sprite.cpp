#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>


//M�todo: Constructor:
Sprite::Sprite() {
	vboID = 0;
}

//M�todo: Destructor:
Sprite::~Sprite() {

	if (vboID != 0) { 
		glDeleteBuffers(1, &vboID); //Borrar el buffer del ID
	}
}

//M�todo: Funci�n para inicializar los elementos
void Sprite::Init(float x, float y, int width, int height, string TexturePath) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	//Si no hay ning�n objeto glew creado
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	/*float VertexData[12]; //Vector que contiene todos los v�rtices del sprite

	//Inicializar los v�rtices del vector VertexData:
	//Coordenadas v�rtice 1
	VertexData[0] = x + width;
	VertexData[1] = y + height;

	//Coordenadas v�rtice 2
	VertexData[2] = x;
	VertexData[3] = y + height;

	//Coordenadas v�rtice 3
	VertexData[4] = x;
	VertexData[5] = y;

	//Coordenadas v�rtice 4
	VertexData[6] = x;
	VertexData[7] = y;

	//Coordenadas v�rtice 5
	VertexData[8] = x + width;
	VertexData[9] = y;

	//Coordenadas v�rtice 6
	VertexData[10] = x + width;
	VertexData[11] = y + height;*/

	texture = ResourceManager::getTexture(TexturePath); //Asignar la im�gen a la textura

	Vertex VertexData[6]; //Variable con los vectores de las posiciones de los v�rtices

	//Inicializar las posiciones UV de la im�gen del sprite para cada v�rtice:
	VertexData[0].SetUV(1.0f, 1.0f); //V�rtice 1
	VertexData[1].SetUV(0.0f, 1.0f); //V�rtice 2
	VertexData[2].SetUV(0.0f, 0.0f); //V�rtice 3
	VertexData[3].SetUV(0.0f, 0.0f); //V�rtice 4
	VertexData[4].SetUV(1.0f, 0.0f); //V�rtice 5
	VertexData[5].SetUV(1.0f, 1.0f); //V�rtice 6


	//Inicializar las posiciones de los v�rtices
	VertexData[0].SetPosition(x + width, y + height);	//V�rtice 1
	VertexData[1].SetPosition(x, y + height);			//V�rtice 2
	VertexData[2].SetPosition(x, y);					//V�rtice 3 
	VertexData[3].SetPosition(x, y);					//V�rtice 4
	VertexData[4].SetPosition(x + width, y);			//V�rtice 5
	VertexData[5].SetPosition(x + width, y + height);	//V�rtice 6

	//Inicializar el color de los v�rtices:
	for (int i = 0; i < 6; i++) {
		VertexData[i].SetColor(255, 255, 0, 255);
	}

	VertexData[1].SetColor(255, 0, 255, 255); //Cambiar color del V�rtice 2
	VertexData[4].SetColor(0, 0, 255, 255); //Cambiar color del V�rtice 5

	//Pasar la informaci�n de los v�rtices al buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboID); //Funci�n para mandarle la informaci�n del buffer de arrays
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW); //Funcipon para mandarle la informaci�n al buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Funci�n para liberar la memoria de todo lo asignado
}

//M�todo: Funci�n para dibujar
void Sprite::draw() {
	glBindTexture(GL_TEXTURE_2D, texture.id); //1.1 Mandar el ID de la texturav
	glBindBuffer(GL_ARRAY_BUFFER, vboID); //1.2 Pasar la informaci�n al buffer

	//Pasar la informaci�n de Posici�n
	glEnableVertexAttribArray(0); //2. Recibe la informaci�n de la posici�n
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //3. Mandar informaci�n de todos los v�rtices al buffer

	//Pasar la informaci�n de Color
	//glEnableVertexAttribArray(1); //Recibe que se le pasa otro atributo (atributo de color)
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); //Recibe la informaci�n de color del v�rtice
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)); //Recibe la informaci�n de las coordenadas uv del v�rtice

	glDrawArrays(GL_TRIANGLES, 0, 6); //Funci�n para dibujar
	glDisableVertexAttribArray(0); //Decirle que ya no va a recibir informaci�n
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Limpiar los datos enviados


}