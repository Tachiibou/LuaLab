#ifndef BLOCK_H
#define BLOCK_H
#include <map>
#include "SFML\Graphics.hpp"


enum BlockType{
	DIRT,
	NRBLOCKTYPES
};

class Block
{
private:
	sf::Sprite* m_sprite;
	sf::Texture* m_texture;

	int m_positionX;
	int m_positionY;
	sf::IntRect m_rect;

	BlockType m_bType;

public:
	Block();
	Block(sf::IntRect rect, BlockType type, std::string textureName);
	
	~Block();

	void setPosition(const int& x, const int& y);
	void assignTexture(std::string name);

	void CrateBlockAt(sf::IntRect rect, BlockType type, std::string textureName);

	sf::Sprite* getSprite() const;

	sf::IntRect getRect() const;
};

#endif