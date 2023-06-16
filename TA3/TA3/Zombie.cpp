#include "Zombie.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

//Constructor
Zombie::Zombie()
{
}

//Destructor
Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	this->path = "Textures/circle.png"; //Obtener ruta de la textura
	this->speed = speed; //Velocidad del zombie
	this->position = position; //Posici�n del zombie

	color.set(255, 50, 108, 255); //Asignarle el color rosado a los zombies

	static std::mt19937 randomEngine(time(nullptr)); //Generar una semilla aleatoria
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f); //Distribuci�n uniforme para generar la direcci�n del zombie

	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine)); //Asirnarle el valor a la direcci�n
	
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}

	direction = glm::vec2(direction);
}

void Zombie::update(const vector<string>& levelData, vector<Human*>& humans,
	vector<Zombie*>& zombies)
{
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randRotate(-40.0, 40.0f);

	position += direction * speed; //Actualizar la posici�n

	if (collideWithLevel(levelData)) {
		direction = glm::rotate(direction, randRotate(randomEngine));
	}
}