#include <iostream>
#include "lua.hpp"


int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int error = luaL_loadfile(L, "script.lua") || lua_pcall(L, 0, 0, 0);

	lua_getglobal(L, "fibbonacci");
	lua_pushinteger(L, 9);

	error = lua_pcall(L, 1, 1, 0);

	std::cout << lua_tonumber(L, -1) << std::endl;

	if (error)
	{
		std::cerr << "Unable to run:" << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}

	delete L;

	lua_State* L2 = luaL_newstate();
	luaL_openlibs(L2);

	int error2 = luaL_loadfile(L2,"script2.lua") || lua_pcall(L2, 0, 0, 0);
	lua_pcall(L2, 0, 0, 0);
	lua_pcall(L2, 0, 0, 0);

	//error2 = lua_pcall(L, 0, 0, 0);

	//std::cout << lua_tostring(L2, -1);

	if (error2)
	{
		std::cerr << "Unable to run:" << lua_tostring(L2, -1) << std::endl;
		lua_pop(L2, 1);
	}

	return 0;
}