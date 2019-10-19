#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"

using namespace std;

const int TILE_WIDTH = 64;

class Level
{
private:
	vector<string> levelData;
	int numHumans;
	void parseLevel();
public:
	Level(const string& filename);
	glm::vec2 playerPosition;
	vector<glm::vec2> zombiesPosition;

	glm::vec2 getPlayerPosition() const {
		return playerPosition;
	}

	int getZombiesVectorSize() const {
		return zombiesPosition.size();
	}

	vector<glm::vec2> getZombiesPosition() const {
		return zombiesPosition;
	}
	int getWidth() const {
		return TILE_WIDTH;
	}
	int getHeight() const {
		return TILE_WIDTH;
	}

	void draw();
	SpriteBacth spriteBatch;

	~Level();
};

