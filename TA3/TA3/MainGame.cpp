#include "MainGame.h"
#include <iostream>
#include "Error.h"
#include <random>
#include <ctime>

using namespace std;

MainGame::MainGame() {
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	camera2D.init(width, height);
}

MainGame::~MainGame() {

}
void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//cout << "Posicion del mousec " << event.motion.x << " " << event.motion.y << endl;
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			glm::vec2 mouseCoords = camera2D.convertToScreenWorld(inputManager.getMouseCoords());
			//cout << "Nueva posicion de acuerdo a camara " <<  mouseCoords.x
				//	<< " " << mouseCoords.y << endl;
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(event.key.keysym.sym);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(event.button.button);
			break;
		}
		handleInput();
	}

}

void MainGame::handleInput()
{
	const float SCALE_SPEED = 0.1f;
	if (inputManager.isKeyPressed(SDLK_q)) {
		camera2D.setScale(camera2D.getScale() + SCALE_SPEED);
	}

	if (inputManager.isKeyPressed(SDLK_e)) {
		camera2D.setScale(camera2D.getScale() - SCALE_SPEED);
	}
	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		//cout << "CLICK IZQUIERDO" << endl;
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		//cout << "CLICK DERECHo" << endl;
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		//cout << "CLICK CENTRO" << endl;
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window.create("Mundo 1", width, height, 0);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Glew not initialized");
	}

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	initLevel();
	initShaders();
}

void MainGame::initLevel() {
	//Inicializar nivel
	levels.push_back(new Level("Level/level1.txt")); //Agregar el nivel 1 al vector de niveles
	currentLevel = 0;

	//Inicializar  el jugador 
	player = new Player(); //Crear el jugador
	player->init(5.0f, levels[currentLevel]->getPlayerPosition(), &inputManager); //Asignar la posici�n del jugador en base a los datos del nivel
	spriteBatch.init(); //Inicializar los datos del jugador

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, levels[currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(
		1, levels[currentLevel]->getHeight() - 2);

	//Inicializar los humanos (humans)
	for (size_t i = 0; i < levels[currentLevel]->getNumHumans(); i++) //Obtener todos los humanos del nivel
	{
		humans.push_back(new Human()); //Crear un nuevo humano
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH); //Crear/Obtener una posici�n aleatoria
		humans.back()->init(1.0f, pos); //Inicializar al humano con la posici�n aleatoria
	}

	//Inicializar los zombies
	const std::vector<glm::vec2>& zombiePosition = levels[currentLevel]->getZombiesPosition(); //Obtener las posiciones de los zombies en el nivel

	for (size_t i = 0; i < zombiePosition.size(); i++) { //Para cada zombie
		zombies.push_back(new Zombie()); //Crear un nuevo zombie
		zombies.back()->init(1.0f, zombiePosition[i]); //Asignarle la posici�n a cada zombie
	}

}

//Dibujar todos los elementos del juego
void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 cameraMatrix = camera2D.getCameraMatrix();
	GLuint pCameraLocation = program.getUniformLocation("pCamera");
	glUniformMatrix4fv(pCameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	spriteBatch.begin(); //Que empieze el sprite batch
	levels[currentLevel]->draw(); //Dibujar el nivel
	player->draw(spriteBatch); //Dibujar al jugador (player)

	//Dibujar todos los humanos
	for (size_t i = 0; i < humans.size(); i++) {
		humans[i]->draw(spriteBatch);
	}

	//Dibujar todos los zombies
	for (size_t i = 0; i < zombies.size(); i++) {
		zombies[i]->draw(spriteBatch);
	}

	spriteBatch.end(); //Que termine el sprite batch
	spriteBatch.renderBatch(); //rederizar los sprites del sprite batch

	glBindTexture(GL_TEXTURE_2D, 0);
	program.unuse();
	window.swapWindow();
}

void MainGame::run() {
	init();
	update();
}

void MainGame::updateElements() {
	player->update(levels[currentLevel]->getLevelData(), humans, zombies);
	for (size_t i = 0; i < humans.size(); i++)
	{
		humans[i]->update(levels[currentLevel]->getLevelData(), humans, zombies);
	}
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		camera2D.update();
		camera2D.setPosition(player->getPosition());
		processInput();
		updateElements();
	}
}