#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
using namespace std;

class InputManager {
//Atributos
	unordered_map<unsigned int, bool> keys; //Mapa que contiene las teclas y sus definiciones
	glm::vec2 mouseCoords; //Variable que almacena las coordenadas del mouse

//Métodos
public:
	//Constructor
	InputManager();

	//Destructor
	~InputManager();

	//Función para obtener las coordenadas del mouse
	glm::vec2 getMouseCoords() {
		return mouseCoords;
	}

	//Función para setear las coordenadas del mouse
	void setMouseCoords(float x, float y);

	//Función para detectar qué tecla se está presionando
	void pressKey(unsigned int keyCode);

	//Función para detectar qué tecla paró de presionarse
	void releaseKey(unsigned int keyCode);

	//Función para determinar si la tecla está siendo presionada o no
	bool isKeyPressed(unsigned int keyCode);
};

