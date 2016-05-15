#include "Map.h"



Map::Map()
{
	this->gameWidth = 800;
	this->gameHeight = 600;

	this->nrBlocksWidth = 20;
	this->nrBlocksHeight = 15;
}


Map::~Map()
{
}

void Map::Draw(sf::RenderWindow* window) {


	for (int i = 0; i < this->mapBlocks.size(); i++) {
		window->draw(*this->mapBlocks.at(i)->getSprite());
	}
}

void Map::Instantiate() {
	int blockSizeX = this->gameWidth / this->nrBlocksWidth;
	int blockSizeY = this->gameHeight / this->nrBlocksHeight;

	for (unsigned int x = 0; x < this->nrBlocksWidth; x++) {
		for (unsigned int y = 0; y < this->nrBlocksHeight; y++) {
			this->mapBlocks.push_back(new Block(sf::IntRect(x*blockSizeX, y*blockSizeY, blockSizeX, blockSizeY), BlockType::DIRT, y%2==0?"Dirt.png":"Grass.png"));

		}
	}
}

void Map::changeMapAt(sf::Keyboard::Key key, sf::Vector2i mousePos) {
	system("cls");

	for (unsigned int x = 0; x < this->nrBlocksWidth; x++) {
		for (unsigned int y = 0; y < this->nrBlocksHeight; y++) {
			if (this->mapBlocks.at(nrBlocksHeight*x+y)->getRect().contains(mousePos)) {
				printf("Inside!!!: %i || Relative to x:%i , y: %i", (x + 1)*y, x, y);
				break;
			}
			
		}
	}
	//for (int i = 0; i < this->mapBlocks.size(); i++) {
	//	if (this->mapBlocks.at(i)->getRect().contains(mousePos)) {
	//		//Lua set at position
	//		printf("Inside!!!: %i || Relative to x:%i , y: %i", i, 
	//		break;
	//	}
	//}
}