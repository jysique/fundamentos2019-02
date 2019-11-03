#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include <iostream>


PlayScreen::PlayScreen(Window* window):_window(window)
{
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	_camera2D.init(_window->getScreenWidth(), _window->getScreenHeight());
	_camera2D.setPosition(
		glm::vec2(
			_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f)
	);
	initSystem();
	initGUI();
	backGround = new Background("Textures/game.png");
	ship = new Ship(6,"Textures/Player.png",&_inputManager);
	enemie = new Enemie(6, "Textures/enemie.png");

	_spriteBatch.init();

}



void PlayScreen::update() {

	_camera2D.update();
	ship->update();
	enemie->update();

//	time++;
	if (time < timetoCreate)
	{
		time++;
		
	}
	else {
		std::cout << "Hola" << endl;
		std::cout << enemiesVector.size() << endl;
		Enemie* newEnemie = new Enemie(6, "Textures/enemie.png");
		enemiesVector.push_back(newEnemie);
		time = 0;
	}

	
	for (size_t i = 0; i < enemiesVector.size(); i++)
	{
		enemiesVector[i]->update();
	}


	//std::cout << time<<endl;
	checkInput();
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
		switch (event.type)
		{
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
	}
}

void PlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();

	ship->draw(_spriteBatch);
	backGround->draw(_spriteBatch);
	enemie->draw(_spriteBatch);
	for (size_t i = 0; i < enemiesVector.size(); i++)
	{
		enemiesVector[i]->draw(_spriteBatch);
	}


	_spriteBatch.end();
	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();

}

void PlayScreen::drawHUD() {
	
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}
