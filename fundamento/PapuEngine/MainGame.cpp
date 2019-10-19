#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include <iostream>
#include "PapuEngine.h"
#include <random>
#include <ctime>

using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Bienvenidos a mi videojuego", _witdh, _height, 0);
	initLevel();
	initShaders();
	//	_spriteBacth.init();
}

void MainGame::initLevel() {
	currentLevel = 0;
	_levelsVector.push_back(new Level("Levels/level1.txt"));
	player = new Player();
	player->init(0.2f, _levelsVector[currentLevel]->getPlayerPosition(), &_inputManager);
	Zombie* zombie;

	for (size_t i = 0; i < _levelsVector[currentLevel]->getZombiesPosition().size(); i++)
	{
		_zombiesVector.push_back(new Zombie());
		_zombiesVector.back()->init(0.2f, _levelsVector[currentLevel]->getZombiesPosition()[i],6);
	}


	_spriteBacth.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(1, _levelsVector[currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randomY(1, _levelsVector[currentLevel]->getHeight() - 2);

}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}




void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	/*GLuint timeLocation =
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation = _program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();

	_levelsVector[currentLevel]->draw();
	player->draw(_spriteBacth,1);
	for (size_t i = 0; i < _zombiesVector.size(); i++)
	{
		_zombiesVector[i]->draw(_spriteBacth,2);
	}

	for (size_t i = 0; i < _spritesVector.size(); i++)
	{
		_spritesVector[i]->draw(_spriteBacth);
	}
	_spriteBacth.end();
	_spriteBacth.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();

	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case  SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		}
		/*
		if (_inputManager.isKeyPressed(SDLK_w)) {
			_camera.setPosition(_camera.getPosition() - glm::vec2(0.0, -CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			_camera.setPosition(_camera.getPosition() - glm::vec2(CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			cout << mouseCoords.x << " " << mouseCoords.y << endl;
		}
		*/

	}

	handleInput();

}

void MainGame::handleInput()
{
	const float CAMERA_SPEED = 0.02;
	const float SCALE_SPEED = 0.001f;

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(1, _levelsVector[currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randomY(1, _levelsVector[currentLevel]->getHeight() - 2);

	if (_inputManager.isKeyPressed(SDLK_p))
	{
		_spritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH, randomY(randomEngine) * TILE_WIDTH);
		_spritesVector.back()->init(pos, 1);
	}
	if (_inputManager.isKeyPressed(SDLK_o))
	{
		_spritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,randomY(randomEngine) * TILE_WIDTH);
		_spritesVector.back()->init(pos, 2);
	}
	if (_inputManager.isKeyPressed(SDLK_i))
	{
		_spritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,randomY(randomEngine) * TILE_WIDTH);
		_spritesVector.back()->init(pos, 3);
	}
	if (_inputManager.isKeyPressed(SDLK_u))
	{
		_spritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH, randomY(randomEngine) * TILE_WIDTH);
		_spritesVector.back()->init(pos, 4);
	}
	if (_inputManager.isKeyPressed(SDLK_y))
	{
		_spritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH, randomY(randomEngine) * TILE_WIDTH);
		_spritesVector.back()->init(pos, 4);
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
}
void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		_camera.setPosition(player->getPosition());
		player->update();
	}
}


MainGame::MainGame() :
	_witdh(800),
	_height(600),
	_gameState(GameState::PLAY),
	_time(0)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
