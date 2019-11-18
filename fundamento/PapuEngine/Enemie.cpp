#include "Enemie.h"
#include "ResourceManager.h"
#include <random>
#include <iostream>
#include <ctime>
#include <string>
//Enemie::Enemie(float _speed, std::string texture)
Enemie::Enemie(float _speed, std::string _tipo,int _altoImagen, int _anchoImagen, int _desfaseAncho, int _desfaseAlto)
{
	speed = _speed;
	position = glm::vec2(800, 100);
	tipo = _tipo;
	altoImagen = _altoImagen;
	anchoImagen = _anchoImagen;
	desfaseAlto = _desfaseAlto;
	desfaseAncho = _desfaseAncho;
	//textureID = ResourceManager::getTexture("Textures/trashhuntB_1.png").id;
}


void Enemie::draw(SpriteBacth& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA color;
	color.set(255, 255, 255, 255);
	glm::vec4 desctRect(position.x, position.y, anchoImagen, altoImagen);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

glm::vec2 Enemie::getPosition() {
	return position;
}

void Enemie::setColor(ColorRGBA color)
{
}

bool Enemie::cliked(glm::vec2 _position)
{
	//int desfase = 20;
	//int altura = ;
	//std::cout << (600 - position.y - altoImagen) << " " << _position.y << std::endl;
	return (_position.y > position.y + altoImagen + desfaseAlto && _position.y < 600 - position.y 
		&& _position.x > position.x+desfaseAncho && _position.x < position.x + anchoImagen - desfaseAncho 
		&& position.x > 0);

}

void Enemie::update(int timeCurrent, int timeChange)
{
	std::string archivo = "Textures/trashhunt";
	if (estado == 1)
	{
		textureID = ResourceManager::getTexture(archivo + tipo + "_1.png").id;
	}
	else if (estado == 2)
	{
		textureID = ResourceManager::getTexture(archivo + tipo + "_2.png").id;
	}
	else if (estado == 3)
	{
		textureID = ResourceManager::getTexture(archivo + tipo + "_3.png").id;
	}
	else if (estado == 4)
	{
		textureID = ResourceManager::getTexture(archivo + tipo + "_4.png").id;
	}
	else if (estado == 5)
	{
		textureID = ResourceManager::getTexture(archivo + tipo + "_5.png").id;
	}
	else if (estado == 6)
	{
		textureID = ResourceManager::getTexture(archivo + tipo + "_6.png").id;
	}
	position.x -= speed;
	if (timeCurrent % timeChange == 0 && clean == false)
	{
		estado++;
	}

}



Enemie::~Enemie()
{
}
