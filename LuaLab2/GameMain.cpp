#include "GameMain.h"
#include "Player.h"

GameMain::GameMain()
{
	this->window_height = 600;
	this->window_width = 800;

	//this->textureHandler = new TextureHandler();
	this->l_map_bridge = new LuaMapBridge();
	this->map = new Map(l_map_bridge);
	this->menu = new Menu(this->window_width, this->window_height);

	this->map->Instantiate();

	this->timeSinceLastFPS = 0;
	FPS = 0;

	//l_map_bridge->setBlock(3, 3, BlockType::WALL);

	//type = l_map_bridge->getBlockType(4, 4);
	//type2 = l_map_bridge->getBlockTexture(4, 4);

	//l_map_bridge->saveMap("Elsas Äventyr2.txt");

	//player = new Player();
	instantiatePlayer();

}


GameMain::~GameMain()
{
	delete this->window;
	delete this->map;
	delete this->menu;
	lua_close(playerState);
	delete TestPlayer;
}

void GameMain::Update(const float & dt)
{
	doFPS(dt);

	//if edit mode
	
	switch (this->gameState)
	{
	case GAME_MENU:
		break;
	case GAME_GAME:
		break;
	case GAME_EDIT:
		this->map->updateMouseRectangle(getMousePos());
		break;
	case GAME_EXIT:
		break;
	default:
		break;
	}
}

void GameMain::Draw() {
	window->clear();
	switch (this->gameState)
	{
	case GAME_MENU:
		this->menu->Draw(this->window);

		break;
	case GAME_GAME:
		this->map->GameDraw(this->window);
		this->window->draw(TestPlayer->getSprite());
		break;
	case GAME_EDIT:
		this->map->EditDraw(this->window);
		break;
	case GAME_EXIT:
		window->close();
		break;
	default:
		break;
	}
	
	window->display();
}

void GameMain::Start()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->window_width, this->window_height), "Shit Game");

	while (window->isOpen())
	{
		this->handleEvents();
		this->deltaTime = clock.restart().asSeconds();
		
		Update(deltaTime);
		Draw();
		
	}
}

void GameMain::doFPS(const float & dt) {
	if (this->timeSinceLastFPS >= 1) {
		std::cout << "FPS: " << FPS << std::endl;
		FPS = 0;
		timeSinceLastFPS = 0;
	}
	FPS += 1;
	timeSinceLastFPS += dt;
}

sf::Vector2i GameMain::getMousePos() {
	return sf::Mouse::getPosition(*this->window);

}

void GameMain::handleEvents() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::KeyPressed)
		{

			playerKeyEvent(event.key.code);
			switch (this->gameState)
			{
			case GAME_MENU:
				this->menu->Update(event.key.code, this->gameState);
				break;
			case GAME_GAME:
				break;
			case GAME_EDIT:
				this->map->changeMapAt(event.key.code, getMousePos());
				break;
			case GAME_EXIT:
				break;
			default:
				break;
			}
			//if (event.key.code == sf::Keyboard::Num1 ||
			//	event.key.code == sf::Keyboard::Num2 ||
			//	event.key.code == sf::Keyboard::Num3 ||
			//	event.key.code == sf::Keyboard::Num4) {

			//	
			//}
		}

		
		
	}
}

void GameMain::playerKeyEvent(sf::Keyboard::Key key) {
	
	/*
	
	(1,0)
	tempPlayer->getpos()+sf::vector2i(1,0);
	bridge
	*/
	
	switch (key)
	{
	case sf::Keyboard::Left:
		this->movePlayer(-1, 0);
		break;
	case sf::Keyboard::Right:
		this->movePlayer(1, 0);
		break;
	case sf::Keyboard::Up:
		this->movePlayer(0, -1);
		break;
	case sf::Keyboard::Down:
		this->movePlayer(0, 1);
		break;
	default:
		break;
	}
}

void GameMain::movePlayer(int x, int y)
{
	int moveX = TestPlayer->getPos().x + x;
	int moveY = TestPlayer->getPos().y + y;

	if (moveX >= 0 && moveX < this->l_map_bridge->getBlockDensity().x && moveY >= 0 && moveY < this->l_map_bridge->getBlockDensity().y) {
		this->map->update(moveX, moveY); // check if we stand on a point


		lua_getglobal(playerState, "updateMovement");
		lua_pushnumber(playerState, x);
		lua_pushnumber(playerState, y);
		std::string type = this->l_map_bridge->getBlockTypeString(TestPlayer->getPos().x + x, TestPlayer->getPos().y + y);
		lua_pushstring(playerState, type.c_str());
		lua_pcall(playerState, 3, 0, 0);
	}
	else
		std::cout << "Trying to walk out of bounds \n";




}

void GameMain::instantiatePlayer() {
	int k = 0;

	playerState = luaL_newstate();

	luaL_openlibs(playerState);

	luaL_newmetatable(playerState, "MetaPlayer");
	luaL_Reg sPlayerReg[] = {
		{ "create", createPlayer },
		{ "testing", printTest },
		{ "setSize", setPlayerSize },
		{ "setPos", setPlayerPosition },
		{ "walk", playerWalk },
		{ NULL, NULL }
	};

	luaL_setfuncs(playerState, sPlayerReg, 0);

	lua_pushvalue(playerState, -1);

	lua_setfield(playerState, -1, "__index");

	lua_setglobal(playerState, "player");


	int error = luaL_loadfile(playerState, "Player.lua") ||
		lua_pcall(playerState, 0, 0, 0);

	lua_getglobal(playerState, "setPlayerSize");

	sf::Vector2f size = this->map->getBlockSize();

	lua_pushnumber(playerState, size.x);
	lua_pushnumber(playerState, size.y);

	lua_pcall(playerState, 2, 0, 0);

	//lua_getglobal(playerState, "getPlayerSizeX");
	//lua_pcall(playerState, 0, 1, 0);
	//
	//float derp = (float)lua_tonumber(playerState, -1);

	//std::cout << "[C++]";
	//TestPlayer->addPoint();
	//TestPlayer->writeText();
	//this->window->draw(*getPlayer(state, 1)->getSprite());
}