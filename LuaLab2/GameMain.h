#pragma once
#include "lua.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include "Map.h"

enum GameState
{
	GAME_MENU,
	GAME_GAME,
	GAME_EDIT,
	GAME_NUMSTATE
};



using namespace std;
class GameMain
{
private:
	int window_width;
	int window_height;
	GameState gameState = GAME_MENU;

	sf::Event event;
	sf::RenderWindow* window;
	sf::Clock clock;
	float lastTime;
	void handleEvents();
	Map* map;

	float FPS;
	float deltaTime;
	float timeSinceLastFPS;

	void doFPS(const float& dt);
	
public:
	GameMain();
	~GameMain();
	void Update(const float& dt);
	void Draw();
	void Start();

	sf::Vector2i getMousePos();
	sf::Vector2i getMouseBlockIndex();
};

