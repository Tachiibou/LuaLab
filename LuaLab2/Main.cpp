#include <iostream>
#include "lua.hpp"
#include "SFML\Graphics.hpp"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

	lua_close(L);

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

	lua_close(L2);

	// SFML CODE AFTER THIS MAGNIFICENT COMMENT

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}