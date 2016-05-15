#ifndef MAP_H
#define MAP_H

#include "Block.h"
#include <vector>
class Map
{
private:
	int nrBlocksWidth, nrBlocksHeight;
	int gameWidth, gameHeight;
	std::vector<Block*> mapBlocks;

public:
	Map();
	~Map();

	void Draw(sf::RenderWindow* window);
	void Instantiate();

	void changeMapAt(sf::Keyboard::Key key, sf::Vector2i mousePos);
};

#endif