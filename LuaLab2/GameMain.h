#pragma once
#include "lua.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include "TextureHandler.h"

using namespace std;
class GameMain
{
private:
	int window_width;
	int window_height;

	sf::Event event;
	sf::RenderWindow* window;
	void handleEvents();
	TextureHandler* textureHandler;
public:
	GameMain();
	~GameMain();
	void Update(const float& dt);
	void Start();
};

