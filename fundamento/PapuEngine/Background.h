#pragma once
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <glm\glm.hpp>
#include <string>


class Background
{
private:
	std::string texture;
	ColorRGBA color;
	int textureID;

public:
	Background(std::string texture);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);
	ColorRGBA getColor()const {
		return color;
	}
	~Background();
};

