#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H
#include "SFML\Graphics.hpp"

enum textureType {
	DIRT,
	GRASS,
	STONE,
	NRTEXTURES
};

class TextureHandler
{
private:
	sf::Texture* textures;

	void loadTexture(textureType type, std::string location);
public:
	TextureHandler();
	~TextureHandler();
};

#endif