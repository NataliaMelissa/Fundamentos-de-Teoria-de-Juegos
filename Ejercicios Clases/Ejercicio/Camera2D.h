#pragma once
#include <glm\gtc\matrix_transform.hpp>

class Camera2D {
//Atributos
	glm::vec2 position; //Posici�n 
	float scale; //Escala del objeto (sirve para el zoom)
	int screenWidth; //ancho
	int screenHeight; //alto
	bool needsUpdateMatrix; //Variable para determinar si se requiere una acualizaci�n o no
	glm::mat4 cameraMatrix; //Matriz c�mara
	glm::mat4 orthoMatrix; //Matriz c�mara ortogonal

//M�todos
public:
	//Constructor
	Camera2D();

	//Destructor
	~Camera2D();

	//Funci�n Actualizar
	void update();

	//Funci�n Inicializar
	void init(int screenWidth, int screenHeight);

	//Funci�n Obtener Posici�n
	glm::vec2 getPosition() {
		return position;
	}

	//Funci�n Definir Posici�n
	void setPosition(const glm::vec2& newPosition) {
		position = newPosition;
		needsUpdateMatrix = true;
	}

	//Funci�n Definir Escala
	void setScale(float newScale) {
		scale = newScale;
		needsUpdateMatrix = true;
	}

	//Funci�n Obtener Matriz de la c�mara
	glm::mat4 getCameraMatrix() {
		return cameraMatrix;
	}
};

