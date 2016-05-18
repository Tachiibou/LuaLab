#pragma once
#include "lua.hpp"
#include <iostream>
#include "SFML\Graphics.hpp"
#include "Block.h"
#include <string>


class LuaMapBridge
{
private:
	lua_State* state;

	void Error(int error, const char* type);
	std::string getFunctionName(BlockType type);
	BlockType getBlockFromLua(std::string blockName);
	

public:
	LuaMapBridge();
	~LuaMapBridge();

	sf::Vector2i getBlockDensity();

	std::string getBlockTypeString(const int &x, const int &y);
	BlockType getBlockType(const int &x, const int &y);
	std::string getBlockTexture(const int &x, const int &y);

	void setBlock(const int &x, const int &y, BlockType type);
	void saveMap(const char* fName);
	void loadMap(const char* fName);
	void createMap(const int &x, const int &y);

	
};