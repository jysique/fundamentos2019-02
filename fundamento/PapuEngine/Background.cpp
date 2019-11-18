#include "Background.h"
#include "ResourceManager.h"


Background::Background(std::string _texture) : texture(_texture)
{
	textureID = ResourceManager::getTexture(texture).id;
	color.set(255, 255, 255, 255);
}

void Background::draw(SpriteBacth& spriteBatch, int ancho, int alto, float posX, float posY) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(posX, posY, ancho, alto);
	spriteBatch.draw(desctRect, uvRect, textureID, 1.0, color);
}


Background::~Background()
{
}
