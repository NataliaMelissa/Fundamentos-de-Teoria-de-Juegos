#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
using namespace std;

class InputManager {
//Atributos
	unordered_map<unsigned int, bool> keys; //Mapa que contiene las teclas y sus definiciones
	glm::vec2 mouseCoords; //Variable que almacena las coordenadas del mouse

//M�todos
public:
	//Constructor
	InputManager();

	//Destructor
	~InputManager();

	//Funci�n para obtener las coordenadas del mouse
	glm::vec2 getMouseCoords() {
		return mouseCoords;
	}

	//Funci�n para setear las coordenadas del mouse
	void setMouseCoords(float x, float y);

	//Funci�n para detectar qu� tecla se est� presionando
	void pressKey(unsigned int keyCode);

	//Funci�n para detectar qu� tecla par� de presionarse
	void releaseKey(unsigned int keyCode);

	//Funci�n para determinar si la tecla est� siendo presionada o no
	bool isKeyPressed(unsigned int keyCode);
};

