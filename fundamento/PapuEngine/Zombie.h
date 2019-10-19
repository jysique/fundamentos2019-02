#pragma once
#include <glm/glm.hpp>
#include "Human.h"

class Zombie :public Human
{
private:
	int type;
public:
	void init(float _speed, glm::vec2 _position, int type);
	Zombie();
	~Zombie();
	void update();
};

