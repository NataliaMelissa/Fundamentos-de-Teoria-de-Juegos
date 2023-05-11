#pragma once
#include <glm\gtc\matrix_transform.hpp>

class Camera2D {
//Atributos
	glm::vec2 position; //Posición 
	float scale; //Escala del objeto (sirve para el zoom)
	int screenWidth; //ancho
	int screenHeight; //alto
	bool needsUpdateMatrix; //Variable para determinar si se requiere una acualización o no
	glm::mat4 cameraMatrix; //Matriz cámara
	glm::mat4 orthoMatrix; //Matriz cámara ortogonal

//Métodos
public:
	//Constructor
	Camera2D();

	//Destructor
	~Camera2D();

	//Función Actualizar
	void update();

	//Función Inicializar
	void init(int screenWidth, int screenHeight);

	//Función Obtener Posición
	glm::vec2 getPosition() {
		return position;
	}

	//Función Definir Posición
	void setPosition(const glm::vec2& newPosition) {
		position = newPosition;
		needsUpdateMatrix = true;
	}

	//Función Definir Escala
	void setScale(float newScale) {
		scale = newScale;
		needsUpdateMatrix = true;
	}

	//Función Obtener Matriz de la cámara
	glm::mat4 getCameraMatrix() {
		return cameraMatrix;
	}
};

