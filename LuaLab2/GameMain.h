#pragma once
#include "lua.hpp"
#include "SFML\Graphics.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Menu.h"




using namespace std;
class GameMain
{
private:
	sf::Text scoreText, editText;
	sf::Font font;
	int window_width;
	int window_height;
	GameState gameState = GAME_MENU;

	sf::Event event;
	sf::RenderWindow* window;
	sf::Clock clock;
	float lastTime;
	void handleEvents();
	Map* map;
	Menu* menu;

	float FPS;
	float deltaTime;
	float timeSinceLastFPS;
	LuaMapBridge* l_map_bridge;

	void doFPS(const float& dt);
	float totalTime;
	

	//PLAYER
	void instantiatePlayer();
	lua_State* playerState;
	void playerKeyEvent(sf::Keyboard::Key key);
	void movePlayer(int x, int y);
	bool win;
	void saveHighScore(float points);
	void loadHighScore();
	float highSscore;
	float getPlayerScore();
	void resetHighScore();
	void setPlayerSpawn();

	void CheckWin();
	void UpdateText();
	
public:
	GameMain();
	~GameMain();
	void Update(const float& dt);
	void Draw();
	void Start();

	sf::Vector2i getMousePos();
	sf::Vector2i getMouseBlockIndex();
};

