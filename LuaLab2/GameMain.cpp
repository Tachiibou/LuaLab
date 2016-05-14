#include "GameMain.h"



GameMain::GameMain()
{
	this->window_height = 600;
	this->window_width = 800;

	this->textureHandler = new TextureHandler();
}


GameMain::~GameMain()
{
	delete this->window;
}

void GameMain::Update(const float & dt)
{

}

void GameMain::Start()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->window_width, this->window_height), "Shit Game");

	while (window->isOpen())
	{
		this->handleEvents();
		

		window->clear();
		window->display();
	}
}

void GameMain::handleEvents() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}