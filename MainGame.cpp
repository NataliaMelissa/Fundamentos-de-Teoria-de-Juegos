#include "MainGame.h"
#include "Error.h"
#include <iostream>

using namespace std;

//Constructor
MainGame::MainGame() {
	n = 2; //Cantidad de Sprites
	cont = 0;
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	time = 0;
	sprite = new Sprite[n];
}

//Destructor
MainGame::~MainGame() {}

//Función para inicializar los shaders
void MainGame::InitShaders() {
	program.CompileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.AddAttribute("VertexPosition"); //Mandarle la posición al shader
	program.AddAttribute("VertexColor"); //Mandarle el colo al shader
	program.LinkShader();
}

//Función para inicializar componentes
void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Hola", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//Validación por si falla la inicialización/pantalla
	if (window == nullptr) {
		FatalError("SDL not initialized"); //Mostrar el error
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window); //variable para que OpenGL pueda usar SDL y Glew a la vez
	GLenum error = glewInit(); //Variable que indica si hay un error o no

	//Condicional para saber si hay un error
	if (error != GLEW_OK) {
		FatalError("Glew not initialized"); //Mostrar el error
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.5f, 0.0f, 1.0f, 1.0f); //Función para darle un color
	InitShaders();
}

//Función para procesar los eventos de mouse y teclado (inputs)
void MainGame::ProcessInput() {
	SDL_Event event; //variable evento SDL

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: //Cuando se preciona una tecla, se saldrá de la pantalla
			gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION: //Detectar la posición del mouse
			cout << "Posicion Mouse: " << event.motion.x << ", " << event.motion.y << endl; //Imprimir la posición (x, y) del mouse
			break;
		}
	}
}

//Método: Función para dibujar elementos en pantalla
void MainGame::draw() {
	glClearDepth(1.0); //Va a comenzar a limpiar la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpia si hay algún elemento más

	GLuint TimeLocation = program.GetUniformLocation("time"); //Obtener la variable time del shader
	glUniform1f(TimeLocation, time); //Mandar la variable time al shader
	time += 0002; //Incrementar la variable time

	program.Use();

	//Dibujar los sprites
	for (int i = 0; i < n; i++) {
		sprite[i].draw(); //Dibujar el sprite
	}

	program.Unuse();

	//Si tengo los elementos actualizados:
	SDL_GL_SwapWindow(window);
}

//Método: Función para actualizar los elementos de las pantallas
void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		ProcessInput();
		cont++;
	}
}

//Método: Función para ejecutar/correr
void MainGame::run() {
	init();
	//if (cont == 0) {
	sprite[0].Init(-1, -1, 1, 1); //Inicializar el sprite1
	//}

	//if (cont == 200) {
	sprite[1].Init(1, 1, -1, -1); //Inicializar el sprite2
	//}

	update();
}