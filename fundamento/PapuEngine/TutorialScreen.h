#pragma once
#include "IGameScreen.h"
#include "Window.h"
#include "GLS_Program.h"
#include "SpriteBacth.h"
#include "Background.h"
#include "Camera2D.h"
#include "SpriteFont.h"
#include "Buttom.h"
#include "AudioPlayer.h"
#include "Enemie.h"

using namespace std;

class TutorialScreen : public IGameScreen
{
	Camera2D camera;
	Background* background = nullptr;
	Window* _window = nullptr;
	bool btnGameClicked;
	GLS_Program _program;
	SpriteBacth _spriteBatch;
	SpriteFont* spriteFont1;
	SpriteFont* spriteFont2;
	SpriteFont* spriteFont3;
	SpriteFont* spriteFont4;
	SpriteFont* spriteFontIntegrante;
	SpriteFont* spriteFontIntegrante1;
	SpriteFont* spriteFontIntegrante2;
	SpriteFont* spriteFontIntegrante3;
	Buttom* buttom;
	AudioPlayer* audioPlayer = nullptr;

	int timeCurrent = 0;
	Enemie* enemie = nullptr;
	bool isClicked;
public:
	TutorialScreen(Window* window);
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void initGUI() override;
	virtual void draw() override;
	virtual void update()override;
	virtual void initSystem()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual int getTutorialScreen() const override;

	virtual void checkInput() override;
	~TutorialScreen();
};

