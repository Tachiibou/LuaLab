#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

enum GameState
{
	GAME_MENU,
	GAME_GAME,
	GAME_EDIT,
	GAME_EXIT
};
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

