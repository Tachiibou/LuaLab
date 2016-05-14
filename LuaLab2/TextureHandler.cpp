#include "TextureHandler.h"



TextureHandler::TextureHandler()
{
	this->textures = new sf::Texture[textureType::NRTEXTURES];

	loadTexture(textureType::DIRT, "Dirt.png");
	loadTexture(textureType::GRASS, "Grass.png");
	loadTexture(textureType::STONE, "Stone.png");
}

void TextureHandler::loadTexture(textureType type, std::string location) {
	if (!textures[type].loadFromFile("./res/" + location)) {
		printf("Couldnt load textur: %s", location);
	}
}


TextureHandler::~TextureHandler()
{
}
