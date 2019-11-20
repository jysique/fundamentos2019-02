#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include <iostream>
#include <sstream>
#include <string.h>

#define LIMIT_LEVEL 10

PlayScreen::PlayScreen(Window * window) :_window(window)
{
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	audioPlayer = new AudioPlayer();
	audioPlayer->addToTrack("Audio/dust.ogg");
	audioPlayer->addToTrack("Audio/effect.ogg");
	audioPlayer->playBackgroundSong();
	backGround = new Background("Textures/trashhunt-game.png");
	ship = new Ship(6, "Textures/trashhunt-user.png", &_inputManager);
	spriteFontPuntaje = new SpriteFont("Fonts/GreatLakesNF.ttf", 64);
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
	delete audioPlayer;
	delete backGround;
	delete ship;
	delete spriteFontPuntaje;
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

	isClicked = false;
	_spriteBatch.init();
}



void PlayScreen::update() {

	_camera2D.update();
	ship->update();

	timeCurrent++;
	if (timeCurrent > level * TIME_TO_CHANGE_LEVEL)
	{
		level++;
		//Level Enemy A
		if (timeChangeSpriteA > 10)
		{
			timeChangeSpriteA -= 6;
		}
		if (timetoCreateA > 0) {
			timetoCreateA -= 30;
		}
		//Level Enemy B
		if (timeChangeSpriteB > 10)
		{
			timeChangeSpriteB -= 6;
		}
		if (timetoCreateB > 0) {
			timetoCreateB -= 30;
		}

		//cout << "level  " << level << endl;
		//speedEnemie *= SPEED_TO_CHANGE_ENEMIE;
		//cout << "speed " << speedEnemieA << endl;
		//cout << "timetoCreate " << timetoCreateA << endl;
		//cout << "speed sprite " << timeChangeSpriteA << endl;
	}

	//Add Enemy A
	if (timeA < timetoCreateA)
	{
		timeA++;
	}
	else{
		//cout << "Hola" << endl;
		Enemie* newEnemie = new Enemie(speedEnemieA, "A",150,150,20,0);
		//newEnemie->setPosition(800, 100);
		enemiesAVector.push_back(newEnemie);
		timeA = 0;
	}

	//Add Enemy B
	if (timeB < timetoCreateB)
	{
		timeB++;
	}
	else {

		Enemie* newEnemie = new Enemie(speedEnemieB, "B", 50, 50, 20, 100);
		enemiesBVector.push_back(newEnemie);
		timeB = 0;
	}

	//Update type A
	for (size_t i = 0; i < enemiesAVector.size(); i++)
	{
		enemiesAVector[i]->update(timeCurrent, timeChangeSpriteA);
		if (enemiesAVector[i]->getPosition().x == -10 && enemiesAVector[i]->getClean() == false)
		{
			trahNoClean++;
			//std::cout << "Llego no limpio el basurero tipo A: " << i << endl;
			//std::cout << "Puntaje: " << trahNoClean << endl;

		}
	}
	//Update type B
	for (size_t i = 0; i < enemiesBVector.size(); i++)
	{
		enemiesBVector[i]->update(timeCurrent, timeChangeSpriteB);
		if (enemiesBVector[i]->getPosition().x == -10 && enemiesBVector[i]->getClean() == false)
		{
			trahNoClean++;
			//std::cout << "Llego no limpio el basurero tipo B: " << i << endl;
			//std::cout << "Puntaje: " << trahNoClean << endl;

		}
	}


	if (trahNoClean == LIMIT_LEVEL)
	{
		lose = true;
		_currentState = ScreenState::CHANGE_NEXT;
	}

	ship->setPosition( _game->_inputManager.getMouseCoords().x - 25 , 475 - _game->_inputManager.getMouseCoords().y);

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
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		//Clicked type A
		//if (!isClicked && buttom->cliked(_game->_inputManager.getMouseCoords())) {
		for (size_t i = 0; i < enemiesAVector.size(); i++) {
			if (!isClicked && enemiesAVector[i]->cliked(_game->_inputManager.getMouseCoords())) {
				//cout << "Apretado " << i << endl;
				enemiesAVector[i]->setEstado(1);
				if (!enemiesAVector[i]->getClean())
				{
					audioPlayer->playSong(1);
				}
				enemiesAVector[i]->setClean(true);
				isClicked = false;
			}
		}

		//Clicked type B
		for (size_t i = 0; i < enemiesBVector.size(); i++) {
			if (!isClicked && enemiesBVector[i]->cliked(_game->_inputManager.getMouseCoords())) {
				//cout << "Apretado " << i << endl;

				enemiesBVector[i]->setEstado(1);
				if (!enemiesBVector[i]->getClean())
				{
					audioPlayer->playSong(1);
				}
				enemiesBVector[i]->setClean(true);
				isClicked = false;
			}
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


	backGround->draw(_spriteBatch, 800, 600, 0.0f, 0.0f);
	
	//Draw type B
	for (size_t i = 0; i < enemiesBVector.size(); i++)
	{
		enemiesBVector[i]->draw(_spriteBatch);
	}

	//Draw type A
	for (size_t i = 0; i < enemiesAVector.size(); i++)
	{
		enemiesAVector[i]->draw(_spriteBatch);
	}
	
	ship->draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	char buffer[256];
	_spriteBatch.begin();
	sprintf(buffer, "TRASH: %d", trahNoClean);
	spriteFontPuntaje->draw(_spriteBatch, buffer,
		glm::vec2(350, 40), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 255, 255), Justification::MIDDLE);

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

int PlayScreen::getTutorialScreen() const
{
	return 0;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;

}
