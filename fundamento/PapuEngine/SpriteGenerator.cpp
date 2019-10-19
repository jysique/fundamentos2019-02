#include "ResourceManager.h"
#include <iostream>
#include "SpriteGenerator.h"

void SpriteGenerator::init(glm::vec2 _position, int _type)
{
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	type = _type;
	position = _position;
}

void SpriteGenerator::draw(SpriteBacth& spritebatch)
{
	static int textureID;
	
	switch (type)
	{

	case 1:
		
		textureID = ResourceManager::getTexture("Textures/humans_01.png").id;
		
		break;
	case 2:
		textureID = ResourceManager::getTexture("Textures/humans_02.png").id;
		
		break;
	case 3:
		textureID = ResourceManager::getTexture("Textures/humans_03.png").id;
		
		break;
	case 4:
		textureID = ResourceManager::getTexture("Textures/humans_04.png").id;
		
		break;
	case 5:
		textureID = ResourceManager::getTexture("Textures/humans_05.png").id;
		
		break;
	}
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, SPRITE_WIDTH, SPRITE_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}
