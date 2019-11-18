#pragma once
#include "Agent.h"
#include <string>
#include <glm/glm.hpp>
#include "InputManager.h"

class Enemie
{
private:
	float speed;
	std::string texture;
	int textureID;
	glm::vec2 position;
	int estado = 1;
	std::string tipo;
	bool clean = false;
	int altoImagen;
	int anchoImagen;
	int desfaseAncho;
	int desfaseAlto;

public:
	Enemie(float _speed, std::string _tipo, int _altoImagen, int _anchoImagen, int _desfaseAncho, int _desfaseAlto);
	void draw(SpriteBacth& spriteBatch);
	void setColor(ColorRGBA color);
	glm::vec2 getPosition()const {
		return position;
	}
	void update(int timeCurrent, int timeChange);
	~Enemie();
	void setEstado(int _estado) {
		this->estado = _estado;
	}
	void setClean(bool _clean) {
		this->clean = _clean;
	}

	int getEstado() {
		return this->estado;
	}

	bool getClean() {
		return this->clean;
	}

	void setSpeed(float _speed) {
		this->speed = _speed;
	}

	glm::vec2 getPosition();
	bool cliked(glm::vec2 _position);
};

