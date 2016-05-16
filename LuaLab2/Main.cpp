#include <iostream>
#include "lua.hpp"
#include "SFML\Graphics.hpp"
#include "GameMain.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameMain* game = new GameMain();

	//lua_State* L = luaL_newstate();
	//luaL_openlibs(L);

	//int error = luaL_loadfile(L, "script.lua") || lua_pcall(L, 0, 0, 0);

	//lua_getglobal(L, "fibbonacci");
	//lua_pushinteger(L, 20);

	//error = lua_pcall(L, 1, 1, 0);

	//std::cout << lua_tonumber(L, -1) << std::endl;

	//if (error)
	//{
	//	std::cerr << "Unable to run:" << lua_tostring(L, -1) << std::endl;
	//	lua_pop(L, 1);
	//}

	//lua_close(L);

	//lua_State* L2 = luaL_newstate();
	//luaL_openlibs(L2);

	////luaL_dofile(L2,"Map.lua");

	//int error2 = luaL_loadfile(L2,"Map.lua") || lua_pcall(L2, 0, 0, 0);

	////error2 = lua_pcall(L, 0, 0, 0);

	////std::cout << lua_tostring(L2, -1);

	//if (error2)
	//{
	//	std::cerr << "Unable to run:" << lua_tostring(L2, -1) << std::endl;
	//	lua_pop(L2, 1);
	//}

	//lua_close(L2);

	// SFML CODE AFTER THIS MAGNIFICENT COMMENT
	game->Start();
	delete game;

	return 0;
}