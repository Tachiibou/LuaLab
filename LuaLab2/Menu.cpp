#include "Menu.h"



void Menu::switchStateUp()
{
	switch (this->menuState)
	{
	case GAME_GAME:
		this->menuState = GAME_EXIT;
		break;
	case GAME_EDIT:
		this->menuState = GAME_GAME;
		break;
	case GAME_EXIT:
		this->menuState = GAME_EDIT;
		break;
	default:
		break;
	}
}

void Menu::switchStateDown()
{
	switch (this->menuState)
	{
	case GAME_GAME:
		this->menuState = GAME_EDIT;
		break;
	case GAME_EDIT:
		this->menuState = GAME_EXIT;
		break;
	case GAME_EXIT:
		this->menuState = GAME_GAME;
		break;
	default:
		break;
	}
}

void Menu::updateText()
{

	if (this->menuState == GAME_GAME)
	{
		this->game.setScale(this->bigSize,1.3f);
		this->edit.setScale(1.0f, 1.0f);
		this->exit.setScale(1.0f, 1.0f);
	}
	else if (this->menuState == GAME_EDIT)
	{
		this->game.setScale(1.0f, 1.0f);
		this->edit.setScale(this->bigSize, 1.3f);
		this->exit.setScale(1.0f, 1.0f);
	}
	else if (this->menuState == GAME_EXIT)
	{
		this->game.setScale(1.0f, 1.0f);
		this->edit.setScale(1.0f, 1.0f);
		this->exit.setScale(this->bigSize, 1.3f);
	}
	float calcX = (this->width / 2);
	this->game.setPosition(calcX - this->game.getLocalBounds().width, 100);
	this->edit.setPosition(calcX - this->game.getLocalBounds().width, 150);
	this->exit.setPosition(calcX - this->game.getLocalBounds().width, 200);

}

Menu::Menu(int width, int height)
{
	this->width = width;
	this->height = height;
	if (!this->font.loadFromFile("arial.ttf"))
	{
		std::cout << "FAIL to load font\n";
	}
	this->game.setFont(this->font);
	this->edit.setFont(this->font);
	this->exit.setFont(this->font);
	this->score.setFont(this->font);

	this->game.setString("Game");
	this->edit.setString("Edit");
	this->exit.setString("Exit");
	this->setScore(0.0f);

	this->game.setColor(sf::Color::Red);
	this->edit.setColor(sf::Color::Green);
	this->exit.setColor(sf::Color::Magenta);
	this->score.setColor(sf::Color::Yellow);

	float calcX = (this->width / 2);
	this->game.setPosition(calcX - this->game.getLocalBounds().width,100);
	this->edit.setPosition(calcX - this->game.getLocalBounds().width,150);
	this->exit.setPosition(calcX - this->game.getLocalBounds().width,200);
	this->score.setPosition(calcX - this->game.getLocalBounds().width, 500);

	this->updateText();
}


Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow* window)
{
	window->draw(this->game);
	window->draw(this->edit);
	window->draw(this->exit);
	window->draw(this->score);
}

void Menu::Update(sf::Keyboard::Key key, GameState& state)
{
	switch (key)
	{
	case sf::Keyboard::Up:
		this->switchStateUp();
		break;
	case sf::Keyboard::Down:
		this->switchStateDown();
		break;
	case sf::Keyboard::Return:
		state = this->menuState;
	default:
		break;
	}
	this->updateText();
}

void Menu::setScore(float score)
{
	this->score.setString("Highscore: " + std::to_string(score));
}

sf::Font Menu::getFont()
{
	return this->font;
}
