#include "Camera2D.h"

//Consturctor
Camera2D::Camera2D() : scale(1.0f),
screenWidth(500),
screenHeight(500),
cameraMatrix(1.0f),
needsUpdateMatrix(true)
{
}

//Destructor
Camera2D::~Camera2D() {}

//M�todo: Funci�n Inicializar la c�mara
void Camera2D::init(int screenWidth, int screenHeight) {
	this->screenWidth = screenWidth; //ancho
	this->screenHeight = screenHeight; //alto
	this->orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight); //c�mara ortogonal
}

//M�todo: Funci�n Actualizar
void Camera2D::update() {

	//Validar si se necesita actualizar
	if (needsUpdateMatrix) { //Requiere actualizaci�n 
		//Hacer la operaci�n de traslaci�n
		glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f); //Par�metros/Datos para la traslaci�n
		cameraMatrix = glm::translate(orthoMatrix, translate); //Hacer la operaci�n de trasladar matrices (mover la matriz)

		//Hacer la escala de la c�mara
		glm::vec3 scaleCamera(this->scale, this->scale, 0.0f); //Valores/formato de la escala
		cameraMatrix = glm::scale(glm::mat4(1.0f), scaleCamera) * cameraMatrix; //Aplicar la escala a la matriz
	}
}


