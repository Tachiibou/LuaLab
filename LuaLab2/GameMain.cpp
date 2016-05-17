#include "GameMain.h"



GameMain::GameMain()
{
	this->window_height = 600;
	this->window_width = 800;

	//this->textureHandler = new TextureHandler();
	this->map = new Map();

	this->map->Instantiate();

	this->timeSinceLastFPS = 0;
	FPS = 0;

	//l_map_bridge->setBlock(3, 3, BlockType::WALL);

	//type = l_map_bridge->getBlockType(4, 4);
	//type2 = l_map_bridge->getBlockTexture(4, 4);

	//l_map_bridge->saveMap("Elsas Äventyr2.txt");


	int k = 0;
}


GameMain::~GameMain()
{
	delete this->window;
	delete this->map;
}

void GameMain::Update(const float & dt)
{
	doFPS(dt);

	//if edit mode
	this->map->updateMouseRectangle(getMousePos());
}

void GameMain::Draw() {
	window->clear();
	this->map->Draw(this->window);
	
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
			this->map->changeMapAt(event.key.code, getMousePos());
			//if (event.key.code == sf::Keyboard::Num1 ||
			//	event.key.code == sf::Keyboard::Num2 ||
			//	event.key.code == sf::Keyboard::Num3 ||
			//	event.key.code == sf::Keyboard::Num4) {

			//	
			//}
		}

		
		
	}
}

