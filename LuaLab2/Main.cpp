#include <iostream>
#include "lua.hpp"


int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	int error = luaL_loadstring(L, "print('Hello World!')") || lua_pcall(L,0,0,0);

	if (error)
	{
		std::cerr << "Unable to run:" << lua_tostring(L, -1);
		lua_pop(L, 1);
	}

	return 0;
}