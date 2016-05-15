#pragma once
#include "lua.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include "TextureHandler.h"
#include "Map.h"

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
	Map* map;
public:
	GameMain();
	~GameMain();
	void Update(const float& dt);
	void Draw();
	void Start();

	sf::Vector2i getMousePos();
	sf::Vector2i getMouseBlockIndex();
};

