#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <string>
#include "Level.h"

class Zombie;
class Human;

const float AGENT_WIDTH = 60.f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Agent
{
protected:
	string path;
	glm::vec2 position;
	float speed;
	Color color;
	void checkTilePosition(const vector<string>& levelData,
		vector<glm::vec2>& collideTilePosition, float x, float y);
	void collideWithTile(glm::vec2 tilePos);

public:
	//Constructor
	Agent();
	
	//Obtener la posición
	glm::vec2 getPosition() {
		return position;
	}
	
	//Asignar la posición
	void setPosition(glm::vec2 position) {
		this->position = position;
	}
	
	virtual void update(const vector<string>& levelData, vector<Human*>& humans,
		vector<Zombie*>& zombies) = 0;

	//Dibujar
	void draw(SpriteBatch& spriteBatch);

	bool collideWithLevel(const vector<string>& levelData);
	
	//Destructor
	virtual ~Agent();

	bool collideWithAgent(Agent* agent);
};
