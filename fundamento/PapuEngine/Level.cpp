#include "Level.h"
#include <fstream>
#include "Error.h"
#include "ResourceManager.h"

void Level::parseLevel()
{
	spriteBatch.init(); //agrupar VBA -pincel y pintado
	spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f); //Centro
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	for (size_t y = 0; y < levelData.size(); y++)
	{
		for (size_t x = 0; x < levelData[y].size(); x++)
		{
			char tile = levelData[y][x]; //recorrer el archivo level
			glm::vec4 desctRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
				//posX posY ancho y alto -> por motivos del curso
			switch (tile)
			{
			case 'R':
			case 'G':
			case 'L':
			case 'B':
				// _,posicion,profundidad,color
				spriteBatch.draw(desctRect, uvRect, ResourceManager::getTexture("Textures/red_bricks.png").id, 0.0f,color);
				break;
			case '@':
				levelData[y][x] = '.';
				playerPosition.x = x*TILE_WIDTH;
				playerPosition.y = y*TILE_WIDTH;
				
				break;
			case 'Z':
				break;
			case '.':
				break;
			default:
				break;
			}
		}
	}
	spriteBatch.end();
}


Level::Level(const string & filename)
{
	ifstream file;
	file.open(filename);
	if (file.fail())
	{
		fatalError("fallo el archivo " + filename + "xdd ");
	}
	string tmp;
	file >> tmp >> numHumans;
	while (getline(file,tmp))
	{
		levelData.push_back(tmp);
	}
	parseLevel();
}

void Level::draw()
{
	spriteBatch.renderBatch();
}

Level::~Level()
{
}
