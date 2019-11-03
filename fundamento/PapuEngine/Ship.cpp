#include "Ship.h"
#include "ResourceManager.h"
#include <SDL\SDL.h>

Ship::Ship(float _speed, std::string texture, InputManager* _inputManager)
{
	speed = _speed;
	position = glm::vec2(350, 100);
	textureID = ResourceManager::getTexture(texture).id;
	inputManager = _inputManager;
}

void Ship::draw(SpriteBacth & spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA color;
	color.set(255, 255, 255, 255);
	glm::vec4 desctRect(position.x, position.y, 50, 50);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

void Ship::setColor(ColorRGBA color)
{
}

void Ship::update()
{

	if (inputManager->isKeyPressed(SDLK_w)) {
		position.y += speed;
	}
	if (inputManager->isKeyPressed(SDLK_s)) {
		position.y -= speed;
	}
	if (inputManager->isKeyPressed(SDLK_a)) {
		position.x -= speed;
	}
	if (inputManager->isKeyPressed(SDLK_d)) {
		position.x += speed;
	}

}

Ship::~Ship()
{

}

