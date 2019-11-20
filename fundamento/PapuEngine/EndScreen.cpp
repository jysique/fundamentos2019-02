#include "EndScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>

EndScreen::EndScreen(Window* window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void EndScreen::initGUI() {
}

void EndScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void EndScreen::destroy() {
	delete buttom;
	delete background;
	delete spriteFont1;
	delete spriteFont2;
	delete audioPlayer;
}

void EndScreen::onExit() {}

void EndScreen::onEntry() {
	initSystem();
	initGUI();
	camera.init(_window->getScreenWidth(), _window->getScreenHeight());
	camera.setPosition(
		glm::vec2(
			_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f)
	);
	isClicked = false;
	_spriteBatch.init();
	background = new Background("Textures/menu.png");
	background1 = new Background("Textures/earth_chan.png");
	spriteFont1 = new SpriteFont("Fonts/GreatLakesNF.ttf", 150);
	spriteFont2 = new SpriteFont("Fonts/GreatLakesNF.ttf", 60);
	buttom = new Buttom("Textures/menu_button.png", 400, 300);

	audioPlayer = new AudioPlayer();
	audioPlayer->addToTrack("Audio/gameover.ogg");
	audioPlayer->playBackgroundSong();

}

void EndScreen::update() {
	camera.update();
	checkInput();
}

void EndScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		if (!isClicked && buttom->cliked(_game->_inputManager.getMouseCoords())) {
			isClicked = true;
			std::cout << "Cambio de pantalla" << endl;
			_currentState = ScreenState::CHANGE_NEXT;
			//destroy();
		}
	}
}

void EndScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();


	background->draw(_spriteBatch, 800, 600, 0.0f, 0.0f);
	background1->draw(_spriteBatch, 200, 200, 550.0f, 0.0f);
	buttom->draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	char buffer[256];
	_spriteBatch.begin();
	sprintf(buffer, "GAME OVER ");
	spriteFont1->draw(_spriteBatch, buffer,
		glm::vec2(100, 120), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255)
	);
	sprintf(buffer, "  :'(( ");
	spriteFont1->draw(_spriteBatch, buffer,
		glm::vec2(100, 30), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255)
	);
	sprintf(buffer, "PLAY AGAIN");
	spriteFont2->draw(_spriteBatch, buffer,
		glm::vec2(420, 310), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255)
	);

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void EndScreen::build() {}

int EndScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int EndScreen::getTutorialScreen() const
{
	return 0;
}

int EndScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

EndScreen::~EndScreen()
{
}
