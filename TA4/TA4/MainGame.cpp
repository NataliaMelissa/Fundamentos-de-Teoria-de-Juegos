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
	contHumans = 0;
	contZombies = 0;
	inicioNivel = false; //El nivel a�n no ha empezado
}

MainGame::~MainGame() {

}
void MainGame::processInput() {
	SDL_Event event;
	bool inputProcessed = false; //Variable para indicar que se detect� el input o no
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			/*cout << "Posicion del mousec " << event.motion.x << " " << event.motion.y << endl;
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			glm::vec2 mouseCoords = camera2D.convertToScreenWorld(inputManager.getMouseCoords());
			//cout << "Nueva posicion de acuerdo a camara " <<  mouseCoords.x
				//	<< " " << mouseCoords.y << endl;*/
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
		//handleInput();
		inputProcessed = true; //indicar que se detect� el input
	}

	//Si se detect� un evento, llamar a handleInput()
	if (inputProcessed == true) {
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

	if (inputManager.isKeyPressed(SDLK_f) && inicioNivel != false) {
		//cout << "Probando" << endl; Comprobar que se ejecutaba la funci�n
		cout << "Zombies: " << contZombies << endl; //Mostrar cantidad de zombies del nivel actualmente
		cout << "Humanos " << contHumans << endl; //Mostrar cantidad de humanos del nivel actualmente
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		//cout << "CLICK IZQUIERDO" << endl;
		createBullet();
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		//cout << "CLICK DERECHo" << endl;
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		//cout << "CLICK CENTRO" << endl;
	}
}

void MainGame::createBullet() {
	glm::vec2 mouseCoords =
		camera2D.convertToScreenWorld(inputManager.getMouseCoords());
	glm::vec2 playerPosition(0, 0);
	glm::vec2 direction = mouseCoords - player->getPosition();
	direction = glm::normalize(direction);
	//bullets.emplace_back(playerPosition, direction, 1.0f, 1000);

	//bullets.push_back(new Bullet(playerPosition, direction, 1.0f, 1000));
	Bullet* bullet = new Bullet(player->getPosition(), direction, 1.0f, 1000);
	bullets.push_back(bullet);
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
	levels.push_back(new Level("Level/level1.txt"));
	currentLevel = 0;
	//inicializar humans,player y zombie
	player = new Player();
	player->init(5.0f, levels[currentLevel]->getPlayerPosition(), &inputManager);
	spriteBatch.init();
	hudBatch.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, levels[currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(
		1, levels[currentLevel]->getHeight() - 2);

	for (size_t i = 0; i < levels[currentLevel]->getNumHumans(); i++)
	{
		humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);
		humans.back()->init(1.0f, pos);
	}

	const std::vector<glm::vec2>& zombiePosition =
		levels[currentLevel]->getZombiesPosition();

	for (size_t i = 0; i < zombiePosition.size(); i++)
	{
		zombies.push_back(new Zombie());
		zombies.back()->init(1.3f, zombiePosition[i]);
	}
	spriteFont = new SpriteFont("Fonts/arial.ttf", 64);

	//Asignarle el n�mero de humanos por nivel
	contHumans = levels[currentLevel]->getNumHumans(); 
	cout << "Humanos: " << contHumans << endl;

	//Asignarle el n�mero de zombies por nivel
	contZombies = zombiePosition.size();
	cout << "Zombies: " << contZombies << endl;
	
	//Indicar que empez� el nivel
	cout << "Valor inicioNivel antes set: " << inicioNivel << endl;
	inicioNivel = true; //Indicar que empez� el nivel
	cout << "Valor inicioNivel luego set: " << inicioNivel << endl;

}

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
	spriteBatch.begin();
	levels[currentLevel]->draw();
	player->draw(spriteBatch);
	for (size_t i = 0; i < humans.size(); i++)
	{
		humans[i]->draw(spriteBatch);
	}
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(spriteBatch);
	}
	for (size_t i = 0; i < zombies.size(); i++)
	{
		zombies[i]->draw(spriteBatch);
	}
	spriteBatch.end();
	spriteBatch.renderBatch();
	drawHud();
	glBindTexture(GL_TEXTURE_2D, 0);
	program.unuse();
	window.swapWindow();
}

void MainGame::drawHud()
{
	glm::mat4 cameraMatrix = camera2D.getCameraMatrix();
	GLuint pCameraLocation = program.getUniformLocation("pCamera");
	glUniformMatrix4fv(pCameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	hudBatch.begin();
	sprintf_s(buffer, "HOLAAAAAAA");
	Color color;
	color.set(255, 255, 255, 255);
	spriteFont->draw(hudBatch, buffer, glm::vec2(0, 0),
		glm::vec2(0.5), 0.0f, Color(255, 255, 255, 255));
	hudBatch.end();
	hudBatch.renderBatch();
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
	for (size_t i = 0; i < zombies.size(); i++) {
		zombies[i]->update(levels[currentLevel]->getLevelData(), humans, zombies);

		for (size_t j = 0; j < humans.size(); j++)
		{
			if (zombies[i]->collideWithAgent(humans[j])) {
				zombies.push_back(new Zombie());
				zombies.back()->init(1.3f, humans[j]->getPosition());
				delete humans[j];
				humans[j] = humans.back();
				humans.pop_back();
			}
		}
	}
	for (size_t i = 0; i < bullets.size();)
	{
		if (bullets[i]->update()) {
			bullets[i] = bullets.back();
			bullets.pop_back();
		}
		else {
			i++;
		}
	}

	//Actualizar valores contador zombies:
	contZombies = zombies.size();

	//Actualizar valores contador humanos:
	contHumans = humans.size();
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