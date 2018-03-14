#include "mGame.hpp"

#include <iostream>

mGame::mGame()
{
	gameState = new state(state::MainGame);
	//menu = new MenuInGame(window->getSize());
}

mGame::~mGame()
{
	delete gameState;
	delete menu;
}

bool mGame::play()
{	
	while (game.getStatus() != Game::status::CleaningUp)
	{
		game.events();

		switch (*gameState)
		{
		case state::MainGame:

			draw();

			break;
		case state::Menu:

			draw();
			menu->draw();

			break;
		case state::Map:
			break;
		}

		//switchState();
		//menu->updateCooldown();

		TimeManager::getTimeOnClocks();
		Painter::Instance().run();
	}

	return true;
}

std::vector<Car*> &mGame::getAllCars()
{
	return cars;
}

void mGame::draw()
{
	Painter::Instance().addToDraw(MapsManager::getMainmap()->getMap());
}

void mGame::switchState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && *gameState == state::MainGame && menu->getCooldownValue() <= 0)
	{
		menu->setPosition(View::getUpLeftCornerPosOfCurrentView(), player->getPosition(), player->getRotation());
		menu->restartCooldownValue();
		window->setMouseCursorVisible(true);
		*gameState = state::Menu;
	}
	else if (menu->canExitMenu() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && *gameState == state::Menu && menu->getCooldownValue() <= 0)
	{
		menu->restartCooldownValue();
		window->setMouseCursorVisible(false);
		*gameState = state::MainGame;
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && *gameState == state::MainGame)
	*gameState = state::Map;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && *gameState == state::Map)
	*gameState = state::MainGame;*/
}
