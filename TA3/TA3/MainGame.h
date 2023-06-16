#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include "Sprite.h"
#include "HLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "InputManager.h"
#include "Level.h"
#include "Player.h"
#include "Human.h"
#include "Zombie.h"
#include "SpriteBatch.h"

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	int width;
	int height;

	SpriteBatch spriteBatch; 
	vector<Level*> levels; //Vector de niveles
	vector<Human*> humans; //Vector de humanos
	vector<Zombie*> zombies; //Vector de zombies
	Player* player; //Jugador (Player)

	int currentLevel; //Indicador del nivel actual
	
	Window window;
	HLSLProgram program;
	Sprite sprite;
	Camera2D camera2D;
	InputManager inputManager;
	
	//Inicializar datos
	void init();

	//Inicializar los datos del nivel
	void initLevel();

	//Procesar el input recibido
	void processInput();

	//Inicializar shaders
	void initShaders();

	//Input del mouse, teclas, etc.
	void handleInput();

	//Actualizar elementos
	void updateElements();

public:
	//Constructor
	MainGame();

	//Destructor
	~MainGame();

	//Enum de estados del juego
	GameState gameState;

	//Ejecutar
	void run();

	//Dibujar los elementos del juego
	void draw();

	//Actualizar todos los elementos del juego
	void update();
};

