#ifndef MAP_H
#define MAP_H



#include "Block.h"
#include <vector>
#include "LuaMapBridge.h"
class Map
{
private:
	int nrBlocksWidth, nrBlocksHeight;
	sf::Vector2i blockGridSize;
	int gameWidth, gameHeight;
	std::vector<Block*> mapBlocks;
	LuaMapBridge* l_map_bridge;

	void Reload();
	
	void changeLuaBlockAt(const int & index, BlockType bType);
	void loadLuaBlockAt(const int & index);
public:
	Map();
	~Map();

	void Draw(sf::RenderWindow* window);
	void Instantiate();

	void changeMapAt(sf::Keyboard::Key key, sf::Vector2i mousePos);
};

#endif