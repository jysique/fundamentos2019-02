#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <string>
#include "InputManager.h"
#include <SDL\SDL.h>

const int AGENT_WIDTH = 60;

class Agent
{
protected:
	glm::vec2 position;
	float speed;
	Color color;

public:
	Agent();
	virtual ~Agent(); // todos los hijos llamaran al destructor
	glm::vec2 getPosition() const { return position; }
	virtual void update() = 0; //  todos los hijos
	void draw(SpriteBacth& spritebatch, int type);

};

