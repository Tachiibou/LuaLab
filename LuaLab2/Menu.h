#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "GameState.h"
class Menu
{
private:
	sf::Text game, exit, edit;
	sf::Font font;
	int width, height;
	GameState menuState = GAME_GAME;
	float bigSize = 1.4f;
	void switchStateUp();
	void switchStateDown();
	void updateText();
public:
	Menu(int width, int height);
	~Menu();
	void Draw(sf::RenderWindow* window);
	void Update(sf::Keyboard::Key key, GameState& state);
};

