#include "Agent.h"
#include "ResourceManager.h"


Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::draw(SpriteBacth & spritebatch, std::string name)
{
	//static int textureID = ResourceManager::getTexture("Textures/Paper_Mario_.png").id;
	static int textureID = ResourceManager::getTexture(name).id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}
