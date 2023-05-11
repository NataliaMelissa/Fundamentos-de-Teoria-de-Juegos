#include "InputManager.h"

//M�todo: Constructor
InputManager::InputManager() : mouseCoords(0.0f, 0.0f) {}

//M�todo: Destructor
InputManager::~InputManager() {}

//M�todo: Funci�n para determinar/Setear las coordenadas del mouse
void InputManager::setMouseCoords(float x, float y) {
    mouseCoords.x = x;
    mouseCoords.y = y;
}

//M�todo: Funci�n para determinar qu� tecla est� siendo presionada
void InputManager::pressKey(unsigned int keyCode) {
    keys[keyCode] = true;
}

//M�todo: Funci�n para determinar qu� tecla ha parado de ser presionada
void InputManager::releaseKey(unsigned int keyCode) {
    keys[keyCode] = false;
}

//M�todo: Funci�n para determinar si una tecla est� siendo presionada o no
bool InputManager::isKeyPressed(unsigned int keyCode) {
    auto it = keys.find(keyCode); //Variable que contiene la tecla

    //Validar si la tecla est� en el array
    if (it != keys.end()) { //Si la tecla s� est� en el map
        return it->second; //retornar la tecla
    }

    return false; //Si la tecla no est� retorna falso
}


