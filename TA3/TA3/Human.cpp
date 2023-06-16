#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Human::Human()
{
}

Human::~Human()
{
}

void Human::init(float speed, glm::vec2 position)
{
	this->path = "Textures/circle.png"; //Camino de la textura
	this->speed = speed; //Asignarle la velocidad
	this->position = position; //Asignarle la posici�n
	color.set(68, 0, 255, 255); //Asignarle el color azul a los humanos

	static std::mt19937 randomEngine(time(nullptr)); //Generar una semilla aleatoria
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f); //Distribuci�n uniforme para generar la direcci�n del humano

	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine)); //Asignarle la direcci�n en base a la semilla y la distribuci�n

	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}

	direction = glm::vec2(direction);
}

void Human::update(const vector<string>& levelData, vector<Human*>& humans,
	vector<Zombie*>& zombies)
{
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randRotate(-40.0, 40.0f);
	position += direction * speed;
	if (collideWithLevel(levelData)) {
		direction = glm::rotate(direction, randRotate(randomEngine));
	}
}