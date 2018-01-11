#include "mGame.hpp"
#include "../../../../../Manager/Texture.hpp"
#include "../../../../../Manager/renderSprites.hpp"
#include "../../../../../Manager/Time.hpp"
#include "../../../../../Manager/Keyboard.hpp"

#include "../../../../GamePhysics/carPhysics/collisionPhysics/Collision.hpp"

mGame::mGame()
{
	gameState = new state(state::MainGame);
	menu = new MenuInGame(window->getSize());

	map = &Map::Instance();

	taxi = new Car(carType::Type::Taxi,sf::Vector2f(4585,4759));
	cars.push_back(taxi);

	/*cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4385, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4885, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4385, 4959)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4885, 4559)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4085, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4685, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4185, 4959)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(4185, 4559)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(3885, 4759)));
	cars.push_back(new Car(carType::Type::Taxi, sf::Vector2f(3885, 4759)));*/

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

			Collision::checkAllCarCollision();
			
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

	player->draw();

	for (unsigned i = 1;i < cars.size();++i)
	{
		cars[i]->draw();
		cars[i]->updatePosition();
	}

	map->drawOn();
}

void mGame::switchState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && *gameState == state::MainGame && menu->getCooldownValue() <=0)
	{
		menu->setPosition(Map::getUpLeftCornerPosOfCurrentView(), player->getPosition());
		menu->restartCooldownValue();
		window->setMouseCursorVisible(true);
		*gameState = state::Menu;
	}
	else if (menu->canExitMenu() &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && *gameState == state::Menu && menu->getCooldownValue() <= 0)
	{
		menu->restartCooldownValue();
		window->setMouseCursorVisible(false);
		*gameState = state::MainGame;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && *gameState == state::MainGame)
		*gameState = state::Map;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && *gameState == state::Map)
		*gameState = state::MainGame;
}
