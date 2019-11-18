#pragma once
#include "Agent.h"
#include <string>
#include <glm/glm.hpp>
#include "InputManager.h"

class Ship
{

private:
	float speed;
	std::string texture;
	int textureID;
	glm::vec2 position;
	InputManager* inputManager;

public:
	Ship(float _speed, std::string texture, InputManager* _inputManager);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);
	glm::vec2 getPosition()const {
		return position;
	}
	void setPosition(int posX, int posY) {
		this->position.x = posX;
		this->position.y = posY;
	}
	void update();
	~Ship();

};

