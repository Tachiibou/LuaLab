#pragma once
#include "SFML\Graphics.hpp"
#include "lua.hpp"
class Player
{
private:
	sf::Vector2f pos;
	sf::Vector2f playerSize;
	sf::Sprite sprite;
	sf::Texture texture;
	int points;
public:
	const int derp = 22;
	void writeText(){
		std::cout << points << std::endl;
	}
	Player(const char* texture){
		if (!this->texture.loadFromFile(texture)) {
			printf("Couldnt load texture for player");
		}
		this->sprite = sf::Sprite(this->texture);
		this->points = 0;
		this->setPosition(0,0);
	}

	sf::Vector2f getPos() {
		return pos;
	}

	void setPosition(int x, int y) {

		pos = sf::Vector2f(x, y);
		this->sprite.setPosition(pos.x * playerSize.x, pos.y * playerSize.y);

	}

	void walk(int x, int y) {
		setPosition(this->pos.x + x, this->pos.y + y);
	}

	sf::Sprite getSprite() {
		return this->sprite;
	}

	void addPoint() {
		this->points++;
	}	

	void setScale(float x, float y) {
		playerSize = sf::Vector2f(x, y);
		this->sprite.setScale(sf::Vector2f(x / (float)this->texture.getSize().x, y / (float)this->texture.getSize().y));
	}
	
	~Player(){}
};

Player* TestPlayer;
lua_State* playerState;

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
	const char* texture = lua_tolstring(state, 1, nullptr);
	lua_pop(state, 1);
	if (texture != nullptr)
	{
		Player** player = reinterpret_cast<Player**>(lua_newuserdata(state, sizeof(Player*)));
		*player = new Player(texture);

		luaL_getmetatable(state, "MetaPlayer");
		lua_setmetatable(state, -2);

		TestPlayer = *player;
		playerState = state;
	}
	else
	{
		printf("Error creating player");
	}

	return 1;
}


int printTest(lua_State* ls) {
	getPlayer(ls, 1)->addPoint();
	getPlayer(ls, 1)->writeText();

	return 0;
}

int setPlayerSize(lua_State* ls) {
	float x = (float)lua_tonumber(ls, -1, nullptr);
	
	float y = (float)lua_tonumber(ls, -2, nullptr);
	lua_pop(ls, 2);

	getPlayer(ls, 1)->setScale(x, y);


	return 0;
}

int setPlayerPosition(lua_State* ls) {

	int y = (int)lua_tonumber(ls, -1, nullptr);

	int x = (int)lua_tonumber(ls, -2, nullptr);

	
	lua_pop(ls, 2);

	getPlayer(ls, 1)->setPosition(x, y);

	return 0;
}

int playerWalk(lua_State* ls) {

	int y = (int)lua_tonumber(ls, -1, nullptr);

	int x = (int)lua_tonumber(ls, -2, nullptr);


	lua_pop(ls, 2);

	getPlayer(ls, 1)->walk(x, y);

	return 0;
}