#include "GameMain.h"
#include "player.h"


GameMain::GameMain()
{
	this->window_height = 600;
	this->window_width = 800;

	//this->textureHandler = new TextureHandler();
	this->map = new Map();
	this->menu = new Menu(this->window_width, this->window_height);

	this->map->Instantiate();

	this->timeSinceLastFPS = 0;
	FPS = 0;

	//l_map_bridge->setBlock(3, 3, BlockType::WALL);

	//type = l_map_bridge->getBlockType(4, 4);
	//type2 = l_map_bridge->getBlockTexture(4, 4);

	//l_map_bridge->saveMap("Elsas Äventyr2.txt");

	//player = new Player();
	int k = 0;

	lua_State* state = luaL_newstate();

	luaL_openlibs(state);

	luaL_newmetatable(state, "MetaPlayer");
	luaL_Reg sPlayerReg[] = {
		{ "create", createPlayer },
		{ "testing", printTest },
		{ NULL, NULL }
	};

	luaL_setfuncs(state, sPlayerReg, 0);

	lua_pushvalue(state, -1);

	lua_setfield(state, -1, "__index");

	lua_setglobal(state, "player");


	int error = luaL_loadfile(state, "Player.lua") ||
		lua_pcall(state, 0, 0, 0);
	

	Player* player = new Player();
	//this->window->draw(*getPlayer(state, 1)->getSprite());

	lua_close(state);
}


GameMain::~GameMain()
{
	delete this->window;
	delete this->map;
	delete this->menu;
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

