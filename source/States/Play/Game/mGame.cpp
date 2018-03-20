#include "mGame.hpp"
#include "../../../Engine/Engine.hpp"
#include "../../../Map/Radar.hpp"
#include "../../../Map/Minimap.hpp"

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

	cars.push_back(new Audi(sf::Vector2f(500, 500), 50));
	cars.push_back(new Taxi(sf::Vector2f(2500, 2500), 0));
	cars.push_back(new Dodge(sf::Vector2f(5200, 5200), 0));
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

			Camera::updateView(player);

			switchCars(carIndex);

			player->control();

			draw();

			break;
		case state::Menu:

			draw();
			menu->draw();

			break;
		case state::Map:

			draw();
			Minimap::Instance().show();

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
	Map::Instance().drawUnder();

	for (const auto &i : cars)
		i->drawShadow();

	for (const auto &i : cars)
	{
		i->draw();

		if (*gameState == state::MainGame)
		{
			i->getMovementClass()->updatePosition();
			i->control();
		}
	}

	if (*gameState == state::MainGame)
	{
		Radar::Instance().update(player);
		Radar::Instance().draw();
	}

	Map::Instance().drawOn();

	//Camera::draw();
}

void mGame::switchState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && *gameState == state::MainGame && menu->getCooldownValue() <= 0 && Minimap::Instance().canRunMinimap())
	{
		menu->setPosition(Camera::getUpLeftCornerPosOfCurrentView(), player->getPosition(), player->getRotation());
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && *gameState == state::MainGame && Minimap::Instance().canRunMinimap())
	{
		const auto &allTiles = TilesManager::getTilesVector();
		Tile* tile = allTiles[static_cast<size_t>(player->getPosition().x / TilesManager::getTileSize())][static_cast<size_t>(player->getPosition().y / TilesManager::getTileSize())];
		sf::Vector2f lenght = player->getPosition() - tile->getTileSprite()->getPosition();

		Minimap::Instance().setPosition(Camera::getUpLeftCornerPosOfCurrentView());
		Minimap::Instance().setPlayerPosition(tile, lenght, player->getRotation());

		window->setMouseCursorVisible(true);
		*gameState = state::Map;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && *gameState == state::Map && Minimap::Instance().canExitMinimap())
	{
		Minimap::Instance().resetCooldown();
		window->setMouseCursorVisible(false);
		*gameState = state::MainGame;
	}
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