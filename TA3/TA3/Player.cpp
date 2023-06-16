#include "Player.h"
#include <SDL/SDL.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float speed, glm::vec2 position, InputManager* inputManager)
{
	this->path = "Textures/circle.png"; //Camino de la textura
	this->speed = speed; //Asignarle la Velocidad
	this->position = position; //Asignarle laPosición
	this->inputManager = inputManager; //Asignarle el Input manager
	color.set(2, 250, 213, 255); //Asignarle el color celeste/cyan al jugador
}

void Player::update(const vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies)
{
	if (inputManager->isKeyPressed(SDLK_w)) {
		position.y += speed;
	}

	if (inputManager->isKeyPressed(SDLK_s)) {
		position.y -= speed;
	}

	if (inputManager->isKeyPressed(SDLK_a)) {
		position.x -= speed;
	}

	if (inputManager->isKeyPressed(SDLK_d)) {
		position.x += speed;
	}
	collideWithLevel(levelData);
}