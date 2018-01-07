#include "Collision.hpp"

#include "carCollisionWithWall.hpp"

#include <iostream>

Collision::Collision()
{
	
}

Collision::~Collision()
{
	
}

void Collision::checkAllCarCollision()
{
	auto &instance = Instance();
	auto &allCars = mGame::Instance().getAllCars();

	for (const auto &i : allCars)
	{
		instance.checkCollisionCarWithWall(i);

		//checkCollisionCarWithCar(i);
		//checkCollisionCarWithHuman(i);
	}
}

void Collision::checkCollisionCarWithWall(Car *car)
{
	carCollisionWithWall::checkCollisions(car);
}

void Collision::checkCollisionCarWithCar()
{

}

void Collision::checkCollisionCarWithHuman()
{

}

sf::Vector2f Collision::getCenterOfHitbox(const sf::CircleShape *hitbox)
{
	return sf::Vector2f(hitbox->getGlobalBounds().left + hitbox->getGlobalBounds().width / 2,
		hitbox->getGlobalBounds().top + hitbox->getGlobalBounds().height / 2);
}