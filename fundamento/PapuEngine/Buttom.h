#pragma once
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <string>
#include <glm/glm.hpp>


class Buttom
{
private:
	std::string texture;
	int textureID;
	glm::vec2 position;

public:

	Buttom(std::string texture, int posX, int posY);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);

	bool cliked(glm::vec2 position);
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition()const {
		return position;
	}

	~Buttom();
};

