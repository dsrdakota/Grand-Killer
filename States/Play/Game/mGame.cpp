#include "mGame.hpp"

#include "../../../Car/Types/Ambulance.hpp"
#include "../../../Car/Types/Audi.hpp"
#include "../../../Car/Types/Black_viper.hpp"
#include "../../../Car/Types/Dodge.hpp"
#include "../../../Car/Types/Mini_truck.hpp"
#include "../../../Car/Types/Police.hpp"
#include "../../../Car/Types/Taxi.hpp"

mGame::mGame()
{
	gameState = new state(state::MainGame);
	player = new Player(sf::Vector2f(1000, 1000),25);
	menu = new MenuInGame();

	cars.push_back(new Audi(sf::Vector2f(500,500),0));
}

mGame::~mGame()
{
	delete player;

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

			View::updateView(player);

			draw();

			break;
		case state::Menu:

			draw();
			menu->draw();

			break;
		case state::Map:
			break;
		}

		switchState();
		menu->updateCooldown();

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

	for (const auto &i : cars)
		i->drawShadow();

	for (const auto &i : cars)
	{
		i->draw();

		if (*gameState == state::MainGame)
			i->control();
	}

	if (*gameState == state::MainGame)
	{
		MapsManager::getRadar()->update(player);
		MapsManager::getRadar()->draw();
	}
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
