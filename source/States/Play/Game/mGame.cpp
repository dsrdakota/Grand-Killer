#include "mGame.hpp"
#include "../../../Engine/Engine.hpp"
#include "../../../Map/Radar.hpp"

#include "../../../Car/Types/Ambulance.hpp"
#include "../../../Car/Types/Audi.hpp"
#include "../../../Car/Types/Black_viper.hpp"
#include "../../../Car/Types/Dodge.hpp"
#include "../../../Car/Types/Mini_truck.hpp"
#include "../../../Car/Types/Police.hpp"
#include "../../../Car/Types/Taxi.hpp"

mGame::mGame()
{
	player = new Player(sf::Vector2f(2500, 2500), 25);

	gameState = new state(state::MainGame);
	menu = new Menu();

	map = &Map::Instance();
	map->init();

	cars.push_back(new Audi(sf::Vector2f(500, 500), 0));
	cars.push_back(new Taxi(sf::Vector2f(2500, 2500), 0));
	cars.push_back(new Audi(sf::Vector2f(5200, 5200), 0));
}

mGame::~mGame()
{
	delete gameState;
	delete menu;
}

bool mGame::play()
{
	size_t carIndex = 0;
	player->getInCar(cars[carIndex]);

	while (game.getStatus() != Game::status::CleaningUp)
	{
		game.events();

		switch (*gameState)
		{
		case state::MainGame:

			Map::Instance().updateView(player->getPosition());

			switchCars(carIndex);

			player->control();

			for (const auto &i : cars)
			{
				i->getMovementClass()->updatePosition();
			}

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
	map->drawUnder();

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
		Radar::Instance().update(player);
		Radar::Instance().draw();
	}

	map->drawOn();
}

void mGame::switchState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && *gameState == state::MainGame && menu->getCooldownValue() <= 0)
	{
		menu->setPosition(Map::getUpLeftCornerPosOfCurrentView(), player->getPosition(), player->getRotation());
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

void mGame::switchCars(size_t &index)
{
	if (cooldown.time->asSeconds() > 0.3f)
	{
		bool isSwitch = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			index++;
			isSwitch = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			index--;
			isSwitch = true;
		}

		if (isSwitch)
		{
			if (index == -1)
				index = cars.size() - 1;
			else if (index == cars.size())
				index = 0;

			player->getOutOfCar();
			player->getInCar(cars[index]);

			*cooldown.time = sf::Time::Zero;
			cooldown.clock->restart();
		}
	}
}