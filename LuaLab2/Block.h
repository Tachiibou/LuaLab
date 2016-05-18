#ifndef BLOCK_H
#define BLOCK_H
#include <map>
#include "SFML\Graphics.hpp"



enum BlockType {
	GRASS,
	DIRT,
	SPAWN,
	WALL,
	POINT,
	GOAL,
	NRTYPES

};

class Block
{
private:
	sf::Sprite* m_sprite;
	sf::Texture m_texture;

	sf::Vector2i m_position;
	sf::IntRect m_rect;

	BlockType m_bType;

public:
	Block();
	Block(sf::Vector2i pos, BlockType type, std::string textureName);
	
	~Block();

	void setPosition(const sf::Vector2i& pos);

	void setScreenPos(sf::Vector2f& blockSize);
	void assignTexture(std::string name);

	void CrateBlockAt(sf::Vector2i pos, BlockType type, std::string textureName);

	sf::Sprite* getSprite() const;

	sf::IntRect getRect() const;

	bool isInside(sf::Vector2i pos) const;

	sf::Vector2i getPos() const;

	void editBlock(BlockType type, std::string textureName);
};

#endif