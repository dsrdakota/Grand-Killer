#include "mGame.hpp"
#include "../../../../../Manager/Texture.hpp"
#include "../../../../../Manager/renderSprites.hpp"
#include "../../../../../Manager/Time.hpp"
#include "../../../../../Manager/Keyboard.hpp"
#include "Radar.hpp"

mGame::mGame()
{
	gameState = new state(state::MainGame);
	menu = new MenuInGame(window->getSize());

	map = &Map::Instance();

	taxi = new Car(carType::Type::Audi, sf::Vector2f(4585, 4759));
	cars.push_back(taxi);

	cars.push_back(new Car(carType::Type::Audi, sf::Vector2f(4385, 4959)));

	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4085, 4959)));
	/*cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(5900, 5800)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4385, 4959)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4885, 4559)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4085, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4685, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4185, 4959)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4185, 4559)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(3885, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(3885, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(3685, 4559)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(3685, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(3485, 4759)));*/

	player = &Player::Instance();
}

mGame::~mGame()
{
	delete gameState;
	delete menu;
}

void mGame::play()
{
	player->giveMeYourCar(taxi);
	while (game.getStatus() != Game::status::CleaningUp)
	{
		game.events();

		switch (*gameState)
		{
		case state::MainGame:

			Map::Instance().updateView(player->getPosition());

			player->move();

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
		renderSprites::Instance().run();
	}
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

	if (player->getState() != Player::playerState::Vehicle)
		player->draw();

	for (const auto &i : cars)
	{
		i->draw();

		if (*gameState == state::MainGame)
			i->updatePosition();
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