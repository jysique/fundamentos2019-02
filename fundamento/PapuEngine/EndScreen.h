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

class EndScreen : public IGameScreen
{
private:
	Camera2D camera;
	Background* background = nullptr;
	Background* background1 = nullptr;
	Window* _window = nullptr;
	bool btnGameClicked;
	GLS_Program _program;
	SpriteBacth _spriteBatch;
	SpriteFont* spriteFont1;
	SpriteFont* spriteFont2;
	//SpriteFont* spriteFont3;
	//SpriteFont* spriteFont4;
	Buttom* buttom;
	AudioPlayer* audioPlayer = nullptr;

	bool isClicked;
public:

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
	EndScreen(Window* window);
	~EndScreen();
};

