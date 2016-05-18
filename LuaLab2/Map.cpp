#include "Map.h"

Map::Map(LuaMapBridge* l_map_bridge)
{
	this->l_map_bridge = l_map_bridge;
	this->gameWidth = 1200;
	this->gameHeight = 800;

	//l_map_bridge = new LuaMapBridge();

	//l_map_bridge->createMap(12, 8);
	l_map_bridge->loadMap("map1.txt");


	this->numBlocks = l_map_bridge->getBlockDensity();

	this->blockSize = sf::Vector2f(float(this->gameWidth) / float(numBlocks.x), (float)this->gameHeight / (float)numBlocks.y);

	//l_map_bridge->saveMap("Elsas Äventyr.txt");

	
	//this->mouseRectangle = sf::RectangleShape(sf::Vector2f(120, 50));
	this->mouseRectangle.setSize(this->blockSize);
	this->mouseRectangle.setOutlineThickness((this->gameWidth / (this->numBlocks.x / this->numBlocks.y))/400);
	
	this->mouseRectangle.setOutlineColor(sf::Color::Black);
	this->mouseRectangle.setPosition(sf::Vector2f(0, 0));
	this->mouseRectangle.setFillColor(sf::Color::Transparent);
	int k = 0;

}


Map::~Map()
{
	for (unsigned int i = 0; i < mapBlocks.size();i++){
		delete this->mapBlocks.at(i);
	}
	

	delete l_map_bridge;
	
}



void Map::GameDraw(sf::RenderWindow* window) {
	for (int i = 0; i < this->mapBlocks.size(); i++) {
		window->draw(*this->mapBlocks.at(i)->getSprite());
	}

	
}

void Map::EditDraw(sf::RenderWindow* window) {
	GameDraw(window);
	//if edit mode
	window->draw(mouseRectangle);
}

void Map::EditUpdate(sf::Keyboard::Key key, GameState& state)
{
	switch (key)
	{
	case sf::Keyboard::S:
		this->l_map_bridge->saveMap(MAP_NAME);
		std::cout << "Map is saved\n";
		state = GameState::GAME_MENU;
		break;
	default:
		break;

	}
}

void Map::updateMouseRectangle(sf::Vector2i mousePos) {
	for (unsigned int i = 0; i < this->mapBlocks.size(); i++) {
		if (this->mapBlocks.at(i)->isInside(mousePos)) {
			this->mouseRectangle.setPosition(sf::Vector2f(this->blockSize.x * this->mapBlocks.at(i)->getPos().x,
				this->blockSize.y* this->mapBlocks.at(i)->getPos().y));
			return;
		}
	}
}

void Map::update(int x, int y)
{
	int index = this->numBlocks.y * x + y;
	
	switch (this->l_map_bridge->getBlockType(x, y))
	{
	case GRASS:
		this->l_map_bridge->setBlock(x, y, DIRT);
		this->loadLuaBlockAt(index);
		break;
	case DIRT:
		this->l_map_bridge->setBlock(x, y, GRASS);
		this->loadLuaBlockAt(index);
		break;
	case SPAWN:
		break;
	case WALL:
		break;
	case POINT:
		this->l_map_bridge->setBlock(x,y,GRASS);
		this->loadLuaBlockAt(index);
		break;
	case GOAL:
		// WIN
		break;
	case NRTYPES:
		break;
	default:
		break;
	}
	
}

void Map::Instantiate() {
	//this->mapBlocks.reserve(blockGridSize.x*blockGridSize.y);
	BlockType blockType;
	std::string blockTexture;

	for (unsigned int x = 0; x < this->numBlocks.x; x++) {
		for (unsigned int y = 0; y < this->numBlocks.y; y++) {

			blockType = l_map_bridge->getBlockType(x, y);
			blockTexture = l_map_bridge->getBlockTexture(x, y);
			this->mapBlocks.push_back(new Block(sf::Vector2i(x, y), BlockType::DIRT, "./res/Dirt.png"));
			this->mapBlocks.back()->setScreenPos(this->blockSize);

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
			BlockType ChangeBlock = BlockType::NRTYPES;
			switch (key)
			{
			case sf::Keyboard::Num1:
				ChangeBlock = BlockType::DIRT;
				break;
			case sf::Keyboard::Num2:
				ChangeBlock = BlockType::GRASS;
				break;
			case sf::Keyboard::Num3:
				ChangeBlock = BlockType::POINT;
				break;
			case sf::Keyboard::Num4:
				ChangeBlock = BlockType::WALL;
				break;
			case sf::Keyboard::Num5:
				ChangeBlock = BlockType::SPAWN;
				break;
			case sf::Keyboard::Num6:
				ChangeBlock = BlockType::GOAL;
				break;
			default:
				break;
			}
			if (ChangeBlock != BlockType::NRTYPES) {
				changeLuaBlockAt(i, ChangeBlock);
				loadLuaBlockAt(i);
			}
			


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

sf::Vector2f Map::getBlockSize() {
	return this->blockSize;
}