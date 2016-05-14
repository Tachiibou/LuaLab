#pragma once
#include "lua.hpp"
#include "SFML\Graphics.hpp"
class GameMain
{
public:
	GameMain();
	~GameMain();
	void Update(const float& dt);
	void Start();
};

