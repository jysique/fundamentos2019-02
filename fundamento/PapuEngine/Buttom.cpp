#include "Buttom.h"
#include "ResourceManager.h"
#include <iostream>
Buttom::Buttom(std::string texture, int posX, int posY)
{
	position = glm::vec2(posX, posY);
	textureID = ResourceManager::getTexture(texture).id;
}

void Buttom::draw(SpriteBacth& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA color;
	color.set(255, 255, 255, 255);
	glm::vec4 desctRect(position.x, position.y, 190, 50);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

void Buttom::setColor(ColorRGBA color)
{
}

bool Buttom::cliked(glm::vec2 _position)
{
	//std::cout << position.x << " " << _position.x <<" " << ((position.x < _position.x) && (position.x + 190 > _position.x)) << std::endl;
	//return (position.x < _position.x) && (position.x + 190 > _position.x) && (position.y < _position.y + 150) && (position.y + 50 > _position.y + 150);
	//std::cout << position.y << " " << _position.y << " " << (_position.y > 450 - position.y   && _position.y < 500 - position.y) << std::endl;
	return (position.x < _position.x) && (position.x + 190 > _position.x) && (_position.y > 450 - position.y) && (_position.y < 500 - position.y);
}

void Buttom::setPosition(glm::vec2 _position)
{

}

Buttom::~Buttom()
{
}
