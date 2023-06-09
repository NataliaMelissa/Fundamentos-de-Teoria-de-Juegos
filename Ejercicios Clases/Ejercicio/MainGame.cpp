#include "MainGame.h"
#include "Error.h"
#include <iostream>

using namespace std;

//Constructor
MainGame::MainGame() {
	n = 2; //Cantidad de Sprites
	//window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	time = 0;
	camera2D.init(width, height); //Inicializar c�mara
	//sprite = new Sprite[n];
}

//Destructor
MainGame::~MainGame() {}

//Funci�n para inicializar los shaders
void MainGame::InitShaders() {
	program.CompileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.AddAttribute("VertexPosition"); //Mandarle la posici�n al shader
	program.AddAttribute("VertexColor"); //Mandarle el color al shader
	program.AddAttribute("VertexUV"); //Mandarle las coordenadas UV al shader
	program.LinkShader();
}

//Funci�n para inicializar componentes
void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	/*window = SDL_CreateWindow("Hola", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//Validaci�n por si falla la inicializaci�n/pantalla
	if (window == nullptr) {
		FatalError("SDL not initialized"); //Mostrar el error
	}
	
	SDL_GLContext glContext = SDL_GL_CreateContext(window); //variable para que OpenGL pueda usar SDL y Glew a la vez

	*/

	window.create("Hola", width, height, 0);

	GLenum error = glewInit(); //Variable que indica si hay un error o no

	//Condicional para saber si hay un error
	if (error != GLEW_OK) {
		FatalError("Glew not initialized"); //Mostrar el error
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.5f, 0.0f, 1.0f, 1.0f); //Funci�n para darle un color
	InitShaders();
}

//Funci�n para procesar los eventos de mouse y teclado (inputs)
void MainGame::ProcessInput() {
	SDL_Event event; //variable evento SDL

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: //Cuando se preciona una tecla, se saldr� de la pantalla
			gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION: //Detectar la posici�n del mouse
			cout << "Posicion Mouse: " << event.motion.x << ", " << event.motion.y << endl; //Imprimir la posici�n (x, y) del mouse
			break;
		}
	}
}

//M�todo: Funci�n para dibujar elementos en pantalla
void MainGame::draw() {
	glClearDepth(1.0); //Va a comenzar a limpiar la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpia si hay alg�n elemento m�s

	program.Use(); //Usar programa

	glActiveTexture(GL_TEXTURE0); //Usar la textura

	//Tiempo
	GLuint TimeLocation = program.GetUniformLocation("time"); //Obtener la variable time del shader
	glUniform1f(TimeLocation, time); //Mandar la variable time al shader
	time += 0002; //Incrementar la variable time

	//C�mara
	glm::mat4 cameraMatrix = camera2D.getCameraMatrix(); //Obtener la matriz de la c�mara
	GLuint pCameraLocation = program.GetUniformLocation("pCamera"); //Obtener la varaibale c�mara del shader
	glUniformMatrix4fv(pCameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0])); //Mandar la variable pCameraLocation al shader

	//Im�gen
	GLuint imageLocation = program.GetUniformLocation("myImage"); //Obtener la variable myImage del shader
	glUniform1i(imageLocation, 0); //Mandar la variable myImage al shader

	//Dibujar los sprites
	/*for (int i = 0; i < n; i++) {
		sprite[i].draw(); //Dibujar el sprite
	}*/
	sprite.draw();

	program.Unuse(); //Dejar de usar el programa

	//Si tengo los elementos actualizados:
	window.swapWindow();
	//SDL_GL_SwapWindow(window);
}

//M�todo: Funci�n para actualizar los elementos de las pantallas
void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		ProcessInput();
	}
}

//M�todo: Funci�n para ejecutar/correr
void MainGame::run() {
	init();
	/*
	sprite[0].Init(-1, -1, 1, 1, "Textures/imagen.png"); //Inicializar el sprite1
	sprite[1].Init(1, 1, -1, -1, "Textures/mario.png"); //Inicializar el sprite2
	*/
	sprite.Init(1, 1, -1, -1, "Textures/mario.png");
	update();
}