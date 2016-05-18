#ifndef MAP_H
#define MAP_H

#include "Block.h"
#include <vector>
#include "LuaMapBridge.h"
#include "Menu.h"
#include "GameState.h"


class Map
{
private:
	const char* MAP_NAME = "map1.txt";
	int nrBlocksWidth, nrBlocksHeight;
	sf::Vector2i blockGridSize;
	int gameWidth, gameHeight;
	std::vector<Block*> mapBlocks;
	LuaMapBridge* l_map_bridge;
	sf::Vector2f blockSize;
	sf::Vector2i numBlocks;

	void Reload();
	
	void changeLuaBlockAt(const int & index, BlockType bType);
	void loadLuaBlockAt(const int & index);

	sf::RectangleShape mouseRectangle;

	
	
public:
	Map(LuaMapBridge* l_map_bridge);
	~Map();

	void GameDraw(sf::RenderWindow* window);
	void EditDraw(sf::RenderWindow* window);
	void EditUpdate(sf::Keyboard::Key key, GameState& state);
	void Instantiate();

	void changeMapAt(sf::Keyboard::Key key, sf::Vector2i mousePos);

	void updateMouseRectangle(sf::Vector2i mousePos);

	void update(int x, int y);

	void reload();

	sf::Vector2f getBlockSize();
};

#endif