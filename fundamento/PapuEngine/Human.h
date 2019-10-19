#pragma once
#include "Agent.h"

class Human:public Agent
{
private:
	int tipo;
	InputManager* inputManager;
	
public:
	Human();
	~Human();

	void update();

	
};

