#include "InputManager.h"

//Método: Constructor
InputManager::InputManager() : mouseCoords(0.0f, 0.0f) {}

//Método: Destructor
InputManager::~InputManager() {}

//Método: Función para determinar/Setear las coordenadas del mouse
void InputManager::setMouseCoords(float x, float y) {
    mouseCoords.x = x;
    mouseCoords.y = y;
}

//Método: Función para determinar qué tecla está siendo presionada
void InputManager::pressKey(unsigned int keyCode) {
    keys[keyCode] = true;
}

//Método: Función para determinar qué tecla ha parado de ser presionada
void InputManager::releaseKey(unsigned int keyCode) {
    keys[keyCode] = false;
}

//Método: Función para determinar si una tecla está siendo presionada o no
bool InputManager::isKeyPressed(unsigned int keyCode) {
    auto it = keys.find(keyCode); //Variable que contiene la tecla

    //Validar si la tecla está en el array
    if (it != keys.end()) { //Si la tecla sí está en el map
        return it->second; //retornar la tecla
    }

    return false; //Si la tecla no está retorna falso
}


