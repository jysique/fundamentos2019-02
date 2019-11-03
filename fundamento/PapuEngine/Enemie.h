#pragma once
#include "Agent.h"
#include <string>
#include <glm/glm.hpp>
#include "InputManager.h"

class Enemie
{
private:
	float speed;
	std::string texture;
	int textureID;
	glm::vec2 position;

public:
	Enemie(float _speed, std::string texture);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);
	glm::vec2 getPosition()const {
		return position;
	}
	void update();
	~Enemie();

};

