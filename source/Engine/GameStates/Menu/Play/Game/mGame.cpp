#include "mGame.hpp"
#include "../../../../../Manager/Texture.hpp"
#include "../../../../../Manager/renderSprites.hpp"
#include "../../../../../Manager/Time.hpp"

#include "../../../../GamePhysics/carPhysics/collisionPhysics/Collision.hpp"

#include <iostream>

mGame::mGame()
{
	cars = new std::vector<Car*>;
	map = &Map::Instance();

	taxi = new Car(carType::Type::Taxi,sf::Vector2f(4585,4759));
	cars->push_back(taxi);

	player = &Player::Instance();
}

mGame::~mGame()
{
	delete cars;
}

void mGame::play()
{
	player->giveMeYourCar(taxi);
	while (game.getStatus() != Game::status::CleaningUp)
	{
		game.events();

		Collision::checkAllCarCollision();

		player->move();

		draw();

		TimeManager::getTimeOnClocks();
	}
}

std::vector<Car*> mGame::getAllCars()
{
	return *cars;
}

void mGame::draw()
{
	map->drawUnder();

	player->draw();

	map->drawOn();

	renderSprites::Instance().run();
}