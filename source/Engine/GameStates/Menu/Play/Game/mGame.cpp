#include "mGame.hpp"
#include "../../../../../Manager/Texture.hpp"
#include "../../../../../Manager/renderSprites.hpp"
#include "../../../../../Manager/Time.hpp"

#include <iostream>

mGame::mGame()
{
	map = &Map::Instance();

	taxi = new Car(carType::Type::Taxi,sf::Vector2f(4585,4759));
	//taxi->setPhycics(taxi);

	player = &Player::Instance();
}

mGame::~mGame()
{
	
}

void mGame::play()
{
	player->giveMeYourCar(taxi);
	while (game.getStatus() != Game::status::CleaningUp)
	{
		game.events();

		player->move();

		map->draw();

		player->draw();

		renderSprites::Instance().run();

		TimeManager::getTimeOnClocks();
	}
}