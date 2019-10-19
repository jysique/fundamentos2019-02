#include "Zombie.h"


void Zombie::init(float _speed, glm::vec2 _position, int _type)
{
	type = _type;
	speed = _speed;
	position = _position;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;
}

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}
void Zombie::update() {
}