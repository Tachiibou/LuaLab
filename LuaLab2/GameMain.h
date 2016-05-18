#pragma once
#include "lua.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include "Map.h"
#include "Menu.h"



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
	Menu* menu;

	float FPS;
	float deltaTime;
	float timeSinceLastFPS;
	LuaMapBridge* l_map_bridge;

	void doFPS(const float& dt);


	//PLAYER
	void instantiatePlayer();
	lua_State* playerState;
	void playerKeyEvent(sf::Keyboard::Key key);
	void movePlayer(int x, int y);
	
public:
	GameMain();
	~GameMain();
	void Update(const float& dt);
	void Draw();
	void Start();

	sf::Vector2i getMousePos();
	sf::Vector2i getMouseBlockIndex();
};

