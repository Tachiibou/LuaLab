#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H
#include "SFML\Graphics.hpp"

class TextureHandler
{
private:
	sf::Texture* textures;

	//void loadTexture(textureType type, std::string location);
public:
	TextureHandler();
	~TextureHandler();
};

#endif