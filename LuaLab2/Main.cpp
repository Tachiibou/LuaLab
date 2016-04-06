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

	return 0;
}