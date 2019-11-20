#include "TutorialScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>

TutorialScreen::TutorialScreen(Window* window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void TutorialScreen::initGUI() {
	audioPlayer = new AudioPlayer();
	audioPlayer->addToTrack("Audio/menu.ogg");
	audioPlayer->addToTrack("Audio/effect.ogg");
	audioPlayer->playBackgroundSong();
}

void TutorialScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void TutorialScreen::destroy() {
	delete enemie;
	delete buttom;
	delete background;
	delete spriteFont1;
	delete spriteFontIntegrante;
	delete audioPlayer;
}

void TutorialScreen::onExit() {}

void TutorialScreen::onEntry() {
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
	enemie = new Enemie(3, "A", 150, 150, 20, 0);
	background = new Background("Textures/trashhunt-game.png");
	spriteFont1 = new SpriteFont("Fonts/GreatLakesNF.ttf", 80);
	spriteFontIntegrante = new SpriteFont("Fonts/GreatLakesNF.ttf", 30);
	buttom = new Buttom("Textures/menu_button.png", 570, 40);


}

void TutorialScreen::update() {
	camera.update();
	checkInput();
	//Update Tutorial
	timeCurrent++;
	enemie->update(timeCurrent, 10);

	if (enemie->getPosition().x == -10 && enemie->getClean() == false)
	{
		std::cout << "Tienes que limpiar la basura :'v" << endl;
	}

}

void TutorialScreen::checkInput() {
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
		//Clicked type tutorial xdd
		if (!isClicked && enemie->cliked(_game->_inputManager.getMouseCoords())) {
			
			enemie->setEstado(1);
			if (enemie->getClean())
			{
					audioPlayer->playSong(1);
			}
			enemie->setClean(true);
			isClicked = false;
			_currentState = ScreenState::CHANGE_NEXT;
			
		}
	}
	
}

void TutorialScreen::draw() {
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
	//Draw tutorial 
	enemie->draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_spriteBatch.begin();

	char buffer[256];
	sprintf(buffer, "INSTRUCCIONES ");
	spriteFont1->draw(_spriteBatch, buffer, glm::vec2(80, 400), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));

	sprintf(buffer, "SALTAR ");
	spriteFont1->draw(_spriteBatch, buffer, glm::vec2(600, 40), glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));

	sprintf(buffer, "Haz click en el tacho");
	spriteFont1->draw(_spriteBatch, buffer, glm::vec2(80, 350), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));

	sprintf(buffer, "para Reciclar la basura ");
	spriteFont1->draw(_spriteBatch, buffer, glm::vec2(80, 300), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));
	
	sprintf(buffer, "INTEGRANTES: ");
	spriteFontIntegrante->draw(_spriteBatch, buffer, glm::vec2(570, 400), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));

	sprintf(buffer, "Renzo Ravelli ");
	spriteFontIntegrante->draw(_spriteBatch, buffer, glm::vec2(570, 380), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));
	
	sprintf(buffer, "Braulio Baldeon ");
	spriteFontIntegrante->draw(_spriteBatch, buffer, glm::vec2(570, 360), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));
	
	sprintf(buffer, "Jose Ysique ");
	spriteFontIntegrante->draw(_spriteBatch, buffer,glm::vec2(570, 340), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));
	
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void TutorialScreen::build() {}

int TutorialScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int TutorialScreen::getTutorialScreen() const
{
	return 0;
}

int TutorialScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

TutorialScreen::~TutorialScreen()
{
}
