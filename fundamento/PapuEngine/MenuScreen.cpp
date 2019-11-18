#include "MenuScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>

MenuScreen::MenuScreen(Window* window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::initGUI() {
	audioPlayer = new AudioPlayer();
	audioPlayer->addToTrack("Audio/menu.ogg");
	audioPlayer->playBackgroundSong();
}

void MenuScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void MenuScreen::destroy() {
	delete buttom;
	delete background;
	delete spriteFont1;
	delete spriteFont2;
	delete audioPlayer;
}

void MenuScreen::onExit() {}

void MenuScreen::onEntry() {
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
	spriteFont1 = new SpriteFont("Fonts/GreatLakesNF.ttf", 150);
	spriteFont2 = new SpriteFont("Fonts/GreatLakesNF.ttf", 150);
	spriteFont3 = new SpriteFont("Fonts/GreatLakesNF.ttf", 80);
	buttom = new Buttom("Textures/menu_button.png", 400, 300);


}

void MenuScreen::update() {
	camera.update();
	checkInput();
}

void MenuScreen::checkInput() {
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

void MenuScreen::draw() {
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

	buttom->draw(_spriteBatch);
	background->draw(_spriteBatch, 800, 600, 0.0f, 0.0f);

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	char buffer1[256];
	char buffer2[256];
	char buffer3[256];
	_spriteBatch.begin();
	sprintf(buffer1, "TRASH HUNT: ");
	sprintf(buffer2, "THE REVENGE ");
	sprintf(buffer3, "PLAY ");
	spriteFont1->draw(_spriteBatch, buffer1,
		glm::vec2(150, 120), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255)
	);
	spriteFont2->draw(_spriteBatch, buffer2,
		glm::vec2(150, 30), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255)
	);
	spriteFont3->draw(_spriteBatch, buffer3,
		glm::vec2(450, 300), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255)
	);

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void MenuScreen::build() {}

int MenuScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int MenuScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

MenuScreen::~MenuScreen()
{
}