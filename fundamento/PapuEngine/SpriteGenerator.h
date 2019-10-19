#pragma once
#include <glm/glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"

const int  SPRITE_WIDTH = 60.f;
const int  SPRITE_RADIUS = SPRITE_WIDTH / 2.0f;

class SpriteGenerator
{
private:
	glm::vec2 position;
	int type;
	Color color;
public:
	glm::vec2 getPosition() const {
		return position;
	}
	void init(glm::vec2 _position, int _type);
	void draw(SpriteBacth& spritebatch);
};

