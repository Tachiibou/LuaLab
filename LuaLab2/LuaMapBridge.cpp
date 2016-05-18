#include "LuaMapBridge.h"
#include "Block.h"


LuaMapBridge::LuaMapBridge()
{
	this->state = luaL_newstate();
	luaL_openlibs(this->state);

	int error = luaL_loadfile(this->state, "Map.lua") || lua_pcall(this->state, 0, 0, 0);

	if (error)
	{
		std::cerr << "Unable to run:" << lua_tostring(this->state, -1) << std::endl;
		lua_pop(this->state, 1);
	}
}

LuaMapBridge::~LuaMapBridge()
{
	lua_close(this->state);
}

sf::Vector2i LuaMapBridge::getBlockDensity() {
	sf::Vector2i returnValue;

	lua_getglobal(this->state, "GetWidth");
	Error(lua_pcall(this->state, 0, 1, 0), "Block Density - X");
	returnValue.x = (int)lua_tonumber(this->state, -1);

	lua_getglobal(this->state, "GetHeight");
	Error(lua_pcall(this->state, 0, 1, 0), "Block Density - y");
	returnValue.y = (int)lua_tonumber(this->state, -1);
	lua_pop(this->state,2);

	

	return returnValue;
}

void LuaMapBridge::Error(int error, const char* type) {
	if (error) {
		printf("There was an error: %s - FIX\n", type);
	}
}

std::string LuaMapBridge::getBlockTypeString(const int & x, const int & y)
{
	std::string returnString;

	lua_getglobal(this->state, "GetType");
	lua_pushinteger(this->state, x);
	lua_pushinteger(this->state, y);

	Error(lua_pcall(this->state, 2, 1, 0), "Block Type");



	returnString = lua_tostring(this->state, -1);
	lua_pop(this->state, 1);
	return returnString;
}

BlockType LuaMapBridge::getBlockType(const int &x, const int &y) {

	std::string returnString;

	lua_getglobal(this->state, "GetType");
	lua_pushinteger(this->state, x);
	lua_pushinteger(this->state, y);

	Error(lua_pcall(this->state, 2, 1, 0), "Block Type");

	

	returnString = lua_tostring(this->state, -1);
	lua_pop(this->state, 1);
	return getBlockFromLua(returnString);
}

std::string LuaMapBridge::getBlockTexture(const int & x, const int & y){
	std::string returnString;

	lua_getglobal(this->state, "GetTexture");
	lua_pushinteger(this->state, x);
	lua_pushinteger(this->state, y);

	Error(lua_pcall(this->state, 2, 1, 0), "Block Texture");

	returnString = lua_tostring(this->state, -1);
	lua_pop(this->state, 1);
	return returnString;
}

void LuaMapBridge::setBlock(const int & x, const int & y, BlockType type){
	lua_getglobal(this->state, getFunctionName(type).c_str());
	lua_pushinteger(this->state, x);
	lua_pushinteger(this->state, y);

	Error(lua_pcall(this->state, 2, 0, 0), "Set Block");
}


void LuaMapBridge::saveMap(const char* fName)
{
	lua_getglobal(this->state, "SaveFile");
	lua_pushstring(this->state, fName);

	Error(lua_pcall(this->state, 1, 0, 0), "Save Map");

}

void LuaMapBridge::loadMap(const char* fName)
{
	lua_getglobal(this->state, "LoadMap");
	lua_pushstring(this->state, fName);

	Error(lua_pcall(this->state, 1, 0, 0), "Load Map");
}

void LuaMapBridge::createMap(const int &x, const int &y)
{
	lua_getglobal(this->state, "CreateMap");

	lua_pushinteger(this->state, x);
	lua_pushinteger(this->state, y);

	Error(lua_pcall(this->state, 2, 0, 0), "Create Map");
}

BlockType LuaMapBridge::getBlockFromLua(std::string blockName) {

	BlockType returnBlock;

	if (blockName == "dirt")
		returnBlock = BlockType::DIRT;
	else if (blockName == "grass")
		returnBlock = BlockType::GRASS;
	else if (blockName == "spawn")
		returnBlock = BlockType::SPAWN;
	else if (blockName == "wall")
		returnBlock = BlockType::WALL;
	else if (blockName == "point")
		returnBlock = BlockType::POINT;
	else if (blockName == "goal")
		returnBlock = BlockType::GOAL;


	return returnBlock;
}


std::string LuaMapBridge::getFunctionName(BlockType type) {
	std::string function;

	switch (type)
	{
	case BlockType::DIRT:
		function = "SetDirt";
		break;
	case BlockType::GRASS:
		function = "SetGrass";
		break;
	case BlockType::SPAWN:
		function = "SetSpawn";
		break;
	case BlockType::WALL:
		function = "SetWall";
		break;
	case BlockType::POINT:
		function = "SetPoint";
		break;
	case BlockType::GOAL:
		function = "SetGoal";
		break;
	default:
		function = "SetDirt";
		break;
	}

	return function;
}

