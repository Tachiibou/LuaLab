#pragma once
#include "SFML\Graphics.hpp"
#include "lua.hpp"
class Player
{
private:
	sf::Vector2i pos;
	sf::Sprite* sprite;
	sf::Texture texture;
	
public:
	const int derp = 22;
	void writeText(){
		printf("in player");
	}
	Player(){
		if (!this->texture.loadFromFile("./res/player.png")) {
			printf("Couldnt load texture for player");
		}
		this->sprite = new sf::Sprite(this->texture);
		this->sprite->setPosition(100, 100);
	}

	//sf::Sprite* getSprite(){
	//	return this->sprite;
	//}

	
	~Player(){}
};

Player* getPlayer(lua_State* state, int n) {
	Player* playerToReturn = nullptr;

	// This checks that the argument is a userdata 
	// with the metatable "MetaMonster"
	void* ptr = luaL_testudata(state, n, "MetaPlayer");

	if (ptr != nullptr)
		playerToReturn = *(Player**)ptr;
	else {

	}

	return playerToReturn;
}


int createPlayer(lua_State* state) {
	const char* name = lua_tolstring(state, 1, nullptr);
	if (name != nullptr)
	{
	Player** player = reinterpret_cast<Player**>(lua_newuserdata(state, sizeof(Player*)));
	*player = new Player();

	luaL_getmetatable(state, "MetaPlayer");
	lua_setmetatable(state, -2);
	}
	else
	{
		printf("Error creating player");
	}

	return 1;
}


int printTest(lua_State* ls) {
	
	getPlayer(ls, 1)->writeText();

	return 0;
}


