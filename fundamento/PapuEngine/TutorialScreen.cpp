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
	delete spriteFont2;
	delete spriteFontIntegrante;
	delete spriteFontIntegrante1;
	delete spriteFontIntegrante2;
	delete spriteFontIntegrante3;
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
	spriteFont2 = new SpriteFont("Fonts/GreatLakesNF.ttf", 80);
	spriteFont3 = new SpriteFont("Fonts/GreatLakesNF.ttf", 80);
	spriteFont4 = new SpriteFont("Fonts/GreatLakesNF.ttf", 80);
	spriteFontIntegrante = new SpriteFont("Fonts/GreatLakesNF.ttf", 30);
	spriteFontIntegrante1 = new SpriteFont("Fonts/GreatLakesNF.ttf", 30);
	spriteFontIntegrante2 = new SpriteFont("Fonts/GreatLakesNF.ttf", 30);
	spriteFontIntegrante3 = new SpriteFont("Fonts/GreatLakesNF.ttf", 30);
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
	char buffer1[256];
	char buffer2[256];
	char buffer3[256];
	char buffer4[256];
	char buffer5[256];
	char buffer6[256];
	char buffer7[256];
	char buffer8[256];
	_spriteBatch.begin();
	sprintf(buffer1, "INSTRUCCIONES ");
	sprintf(buffer2, "SALTAR ");
	sprintf(buffer3, "INTEGRANTES: ");
	sprintf(buffer4, "Jose Ysique ");
	sprintf(buffer5, "Braulio Baldeon ");
	sprintf(buffer6, "Renzo Ravelli ");
	sprintf(buffer7, "Haz click en el tacho");
	sprintf(buffer8, "para Reciclar la basura ");
	spriteFont1->draw(_spriteBatch, buffer1,glm::vec2(80, 400), glm::vec2(0.5), 0.0f,ColorRGBA(0, 0, 0, 255));
	spriteFont2->draw(_spriteBatch, buffer2,glm::vec2(600, 40), glm::vec2(0.5), 0.0f,ColorRGBA(255, 255, 255, 255));
	spriteFont3->draw(_spriteBatch, buffer7, glm::vec2(80, 350), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));
	spriteFont4->draw(_spriteBatch, buffer8, glm::vec2(80, 300), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));
	spriteFontIntegrante->draw(_spriteBatch, buffer3,glm::vec2(570, 400), glm::vec2(0.5), 0.0f,ColorRGBA(0, 0, 0, 255));
	spriteFontIntegrante1->draw(_spriteBatch, buffer4,glm::vec2(570, 380), glm::vec2(0.5), 0.0f,ColorRGBA(0, 0, 0, 255));
	spriteFontIntegrante2->draw(_spriteBatch, buffer5,glm::vec2(570, 360), glm::vec2(0.5), 0.0f,ColorRGBA(0, 0, 0, 255));
	spriteFontIntegrante3->draw(_spriteBatch, buffer6,glm::vec2(570, 340), glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255));
	
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
