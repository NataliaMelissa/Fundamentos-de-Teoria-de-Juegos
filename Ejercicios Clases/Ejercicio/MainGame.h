#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include "Sprite.h"
#include "HLSL_Program.h"
#include "Window.h"

enum class GameState { PLAY, EXIT };

class MainGame {
	//Atributos
	int n; //Cantidad de sprites
	int width; //ancho del escenario
	int height; //Alto del escenario
	float time; //Variable de tiempo usada por el shader
	//SDL_Window* window; //variable para dibujar en pantalla 
	//Sprite* sprite; //Vector de Sprites
	Window window;
	Sprite sprite;
	HLSL_Program program; //variable del programa

	//Funciones
	void init();

	void ProcessInput();

	void InitShaders();

public:
	//Constructor
	MainGame();

	//Destructor
	~MainGame();

	GameState gameState; //Variable pública

	//Métodos
	void run(); //Función para ejecutar

	void draw(); //Función para dibujar

	void update(); //Función para actualizar

};


/* Información sobre las clases:
- GameState = Contiene los estados de juego
- MainGame = Clase controladora del juego
*/

