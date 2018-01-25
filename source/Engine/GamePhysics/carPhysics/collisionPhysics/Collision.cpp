#include "Collision.hpp"

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

	for (size_t i=0;i<allCars.size();++i)
	{
		instance.checkCollisionCarWithWall(allCars[i]);

		// check !!!

		for (size_t j = i+1;j<allCars.size();++j)
			instance.checkCollisionCarWithCar(allCars[i], allCars[j]);

		//checkCollisionCarWithHuman(i);
	}
}

void Collision::checkCollisionCarWithWall(Car *car)
{
	carCollisionWithWall::checkCollisions(car);
}

void Collision::checkCollisionCarWithCar(Car *car1, Car *car2)
{
	carCollisionWithCar::checkCollisions(car1, car2);
}

void Collision::checkCollisionCarWithHuman()
{

}

sf::Vector2f Collision::getCenterOfHitbox(const sf::CircleShape *hitbox)
{
	return sf::Vector2f(hitbox->getGlobalBounds().left + hitbox->getGlobalBounds().width / 2,
		hitbox->getGlobalBounds().top + hitbox->getGlobalBounds().height / 2);
}