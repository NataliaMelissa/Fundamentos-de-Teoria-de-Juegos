#pragma once
#include "Agent.h"

class Zombie : public Agent
{
protected:
	glm::vec2 direction;

public:
	//Constructor
	Zombie(); 

	//Destructor
	~Zombie(); 

	//Inicializar valores
	void init(float speed, glm::vec2 position); 

	//Actualizar valores
	void update(const vector<string>& levelData, vector<Human*>& humans,
		vector<Zombie*>& zombies); 

};

