#include "Block.h"



Block::Block(sf::Vector2i pos, BlockType type, std::string textureName)
{
	CrateBlockAt(pos, type, textureName);
}

Block::Block() {

}


Block::~Block()
{
}

void Block::setPosition(const sf::Vector2i& pos) {
	this->m_position = pos;
	
}

void Block::setScreenPos(sf::Vector2f& blockSize) {
	this->m_rect =sf::IntRect(blockSize.x*this->m_position.x, blockSize.y*this->m_position.y, blockSize.x, blockSize.y);
	
	//this->m_sprite->setTextureRect(m_rect);
	this->m_sprite.setPosition(m_rect.left, m_rect.top);
	float scaleX = (float)m_rect.width / (float)this->m_texture.getSize().x;
	float scaleY = (float)m_rect.height / (float)this->m_texture.getSize().y;
	this->m_sprite.setScale(sf::Vector2f(scaleX, scaleY));
}

void Block::assignTexture(std::string name) {
	
	
	if (!this->m_texture.loadFromFile( name)) {
		printf("Couldnt load textur: %s", name);
	}

	

}

sf::Sprite Block::getSprite() const {
 	return this->m_sprite;
}

void Block::CrateBlockAt(sf::Vector2i pos, BlockType type, std::string textureName) {
	this->assignTexture(textureName);
	this->m_sprite = sf::Sprite(this->m_texture);
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

sf::Vector2i Block::getPos() const {
	return this->m_position;
}

void Block::editBlock(BlockType type, std::string textureName) {
	this->assignTexture(textureName);
	sf::Vector2f oldPos = this->m_sprite.getPosition();
	this->m_sprite = sf::Sprite(this->m_texture);

	this->m_sprite.setPosition(oldPos);


	this->m_bType = type;
}