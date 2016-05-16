#include "Block.h"



Block::Block(sf::Vector2i pos, BlockType type, std::string textureName)
{
	this->m_texture = new sf::Texture();
	CrateBlockAt(pos, type, textureName);
}

Block::Block() {

}


Block::~Block()
{
	delete this->m_sprite;
	delete this->m_texture;
}

void Block::setPosition(const sf::Vector2i& pos) {
	this->m_position = pos;
	
}

void Block::setScreenPos(const int& windowX, const int& windowY, const int &nrBLockX, const int&nrBlockY) {
	this->m_rect =sf::IntRect((windowX / nrBLockX)*this->m_position.x, (windowY/ nrBlockY)*this->m_position.y, windowX / nrBLockX, windowY / nrBlockY);

	this->m_sprite->setTextureRect(m_rect);
	this->m_sprite->setPosition(m_rect.left, m_rect.top);
}

void Block::assignTexture(std::string name) {
	
	if (!this->m_texture->loadFromFile("res/" + name)) {
		printf("Couldnt load textur: %s", name);
	}

}

sf::Sprite* Block::getSprite() const {
 	return this->m_sprite;
}

void Block::CrateBlockAt(sf::Vector2i pos, BlockType type, std::string textureName) {
	this->assignTexture(textureName);
	this->m_sprite = new sf::Sprite(*this->m_texture);
	//this->m_sprite->setTextureRect(rect);
	
	this->m_position = pos;

	this->m_bType = type;

	//this->m_rect = this->m_sprite->getTextureRect();
}

sf::IntRect Block::getRect() const {
	return this->m_rect;
}

bool Block::isInside(sf::Vector2i pos) const {
	return this->m_rect.contains(pos);
}