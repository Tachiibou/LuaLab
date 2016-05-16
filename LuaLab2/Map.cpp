#include "Map.h"



Map::Map()
{
	this->gameWidth = 800;
	this->gameHeight = 600;

	l_map_bridge = new LuaMapBridge();

	//l_map_bridge->createMap(50, 50);
	l_map_bridge->loadMap("Elsas Äventyr.txt");

	
	
	BlockType type = l_map_bridge->getBlockType(4, 4);
	std::string type2 = l_map_bridge->getBlockTexture(4, 4);

	int k = 0;
}


Map::~Map()
{
	for (unsigned int i = 0; i < mapBlocks.size();i++){
		delete this->mapBlocks.at(i);
	}
	l_map_bridge->saveMap("Elsas Äventyr.txt");
}

void Map::Draw(sf::RenderWindow* window) {


	for (int i = 0; i < this->mapBlocks.size(); i++) {
		window->draw(*this->mapBlocks.at(i)->getSprite());
	}
}

void Map::Instantiate() {
	blockGridSize = l_map_bridge->getBlockDensity();
	//this->mapBlocks.reserve(blockGridSize.x*blockGridSize.y);
	BlockType blockType;
	std::string blockTexture;

	for (unsigned int x = 0; x < this->blockGridSize.x; x++) {
		for (unsigned int y = 0; y < this->blockGridSize.y; y++) {

			blockType = l_map_bridge->getBlockType(x, y);
			blockTexture = l_map_bridge->getBlockTexture(x, y);
			this->mapBlocks.push_back(new Block(sf::Vector2i(x, y), BlockType::DIRT, "./res/Dirt.png"));
			this->mapBlocks.back()->setScreenPos(this->gameWidth, this->gameHeight, this->blockGridSize.x, this->blockGridSize.y);

			loadLuaBlockAt(mapBlocks.size() - 1);
		}
	}
}

void Map::changeLuaBlockAt(const int & index, BlockType bType) {
	sf::Vector2i pos = this->mapBlocks.at(index)->getPos();

	l_map_bridge->setBlock(pos.x, pos.y, bType);

}

void Map::loadLuaBlockAt(const int & index) {
	BlockType blockType;
	std::string blockTexture;
	sf::Vector2i pos = this->mapBlocks.at(index)->getPos();

	blockType = l_map_bridge->getBlockType(pos.x, pos.y);
	blockTexture = l_map_bridge->getBlockTexture(pos.x, pos.y);

	this->mapBlocks.at(index)->editBlock(blockType, blockTexture);
	//this->mapBlocks.back()->setScreenPos(this->gameWidth, this->gameHeight, this->blockGridSize.x, this->blockGridSize.y);
}

void Map::changeMapAt(sf::Keyboard::Key key, sf::Vector2i mousePos) {
	//system("cls");
	for (unsigned int i = 0; i < this->mapBlocks.size(); i++) {
		if (this->mapBlocks.at(i)->isInside(mousePos)) {

			changeLuaBlockAt(i, BlockType::GRASS);
			loadLuaBlockAt(i);


			//printf("Inside!!!: || Relative to x:%i , y: %i", this->mapBlocks.at(i)->getPos().x, this->mapBlocks.at(i)->getPos().y);
		}
	}
}

void Map::Reload() {
	if (this->mapBlocks.size() > 0) {
		for (unsigned int i = 0; i < this->mapBlocks.size(); i++) {
			delete mapBlocks.at(i);
		}

		this->mapBlocks.clear();
	}

	Instantiate();
}