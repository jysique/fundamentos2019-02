#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "SpriteFont.h"
#include "Background.h"
#include "Ship.h"
#include "Enemie.h"
#include "AudioPlayer.h"

// por defecto es 1000
#define TIME_TO_CHANGE_LEVEL 1000

// por defecto es 1.3
//#define SPEED_TO_CHANGE_ENEMIE 1.4

// por defecto es 3
#define SPEED_ENEMY_BEGIN_A  3
#define SPEED_ENEMY_BEGIN_B  6

// por defecto es 200
#define TIME_TO_CREATE_ENEMY_A 200
#define TIME_TO_CREATE_ENEMY_B 100

#define TIME_TO_CHANGE_SPRITE_ENEMY_A 30
#define TIME_TO_CHANGE_SPRITE_ENEMY_B 10

class PlayScreen : public IGameScreen
{
private:
	GLS_Program _program;

	Camera2D _camera2D;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	SpriteBacth _hudBach;
	Camera2D _hudCamera;
	SpriteFont* spriteFontPuntaje;
	SpriteFont* spriteFont;
	InputManager _inputManager;
	AudioPlayer* audioPlayer = nullptr;

	Background* backGround = nullptr;
	Ship* ship = nullptr;
	vector<Enemie*> enemiesAVector;
	vector<Enemie*> enemiesBVector;
	
	int timeCurrent = 0;
	bool lose = false;
	int level = 1;
	int puntaje = 0;
	bool isClicked;
	int trahNoClean = 0;

	//Enemigo A
	int timeA = 0;
	int timetoCreateA = TIME_TO_CREATE_ENEMY_A;
	float speedEnemieA = SPEED_ENEMY_BEGIN_A;
	int timeChangeSpriteA = TIME_TO_CHANGE_SPRITE_ENEMY_A;

	//Enemigo B
	int timeB = 0;
	int timetoCreateB = TIME_TO_CREATE_ENEMY_B;
	float speedEnemieB = SPEED_ENEMY_BEGIN_B;
	int timeChangeSpriteB = TIME_TO_CHANGE_SPRITE_ENEMY_B;


	
	void drawHUD();
public:
	PlayScreen(Window* window);
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
	~PlayScreen();
};



