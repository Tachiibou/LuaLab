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

	sf::Vector2i m_position;
	sf::IntRect m_rect;

	BlockType m_bType;

public:
	Block();
	Block(sf::Vector2i pos, BlockType type, std::string textureName);
	
	~Block();

	void setPosition(const sf::Vector2i& pos);

	void setScreenPos(const int& windowX, const int& windowY, const int &nrBLockX, const int&nrBlockY);
	void assignTexture(std::string name);

	void CrateBlockAt(sf::Vector2i pos, BlockType type, std::string textureName);

	sf::Sprite* getSprite() const;

	sf::IntRect getRect() const;

	bool isInside(sf::Vector2i pos) const;
};

#endif