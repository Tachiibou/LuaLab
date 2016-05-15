#include "Block.h"



Block::Block(sf::IntRect rect, BlockType type, std::string textureName)
{
	this->m_texture = new sf::Texture();
	CrateBlockAt(rect, type, textureName);
}

Block::Block() {

}


Block::~Block()
{
}

void Block::setPosition(const int& x, const int& y) {
	this->m_positionX = x;
	this->m_positionY = y;

	this->m_sprite->setPosition(this->m_positionX, this->m_positionY);
}

void Block::assignTexture(std::string name) {
	
	if (!this->m_texture->loadFromFile("res/" + name)) {
		printf("Couldnt load textur: %s", name);
	}

}

sf::Sprite* Block::getSprite() const {
	return this->m_sprite;
}

void Block::CrateBlockAt(sf::IntRect rect, BlockType type, std::string textureName) {
	this->assignTexture(textureName);
	this->m_sprite = new sf::Sprite(*this->m_texture);
	this->m_sprite->setTextureRect(rect);

	this->setPosition(rect.left, rect.top);

	this->m_bType = type;

	this->m_rect = this->m_sprite->getTextureRect();
}

sf::IntRect Block::getRect() const {
	return this->m_rect;
}