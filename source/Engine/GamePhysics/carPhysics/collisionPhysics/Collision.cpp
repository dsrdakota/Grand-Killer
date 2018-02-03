#include "Collision.hpp"

Collision::Collision()
{
	
}

Collision::~Collision()
{
	
}

void Collision::checkAllCarsCollision()
{
	auto &instance = Instance();
	auto &allCars = mGame::Instance().getAllCars();

	for (size_t i=0;i<allCars.size();++i)
	{
		instance.checkCollisionCarWithWall(allCars[i]);

		for (size_t j = i+1;j<allCars.size();++j)
			instance.checkCollisionCarWithCar(allCars[i], allCars[j]);

		//checkCollisionCarWithHuman(i);
	}
}

Car::collisionSide Collision::checkAllCarCollision(Car *car)
{
	auto &instance = Instance();
	auto &allCars = mGame::Instance().getAllCars();

	Car::collisionSide side;

	side = instance.checkCollisionCarWithWall(car);

	if (side == Car::collisionSide::None)
	{
		for (size_t i = 0;i < allCars.size();++i)
		{
			side = instance.checkCollisionCarWithCar(car, allCars[i]);
			if (side != Car::collisionSide::None)
				return side;
		}

		//checkCollisionCarWithHuman(i);
	}
	return side;
}


Car::collisionSide Collision::checkCollisionCarWithWall(Car *car)
{
	return carCollisionWithWall::checkCollisions(car);
}

Car::collisionSide Collision::checkCollisionCarWithCar(Car *car1, Car *car2)
{
	return carCollisionWithCar::checkCollisions(car1, car2);
}

void Collision::checkCollisionCarWithHuman()
{

}

sf::Vector2f Collision::getCenterOfHitbox(const sf::CircleShape *hitbox)
{
	return sf::Vector2f(hitbox->getGlobalBounds().left + hitbox->getGlobalBounds().width / 2,
		hitbox->getGlobalBounds().top + hitbox->getGlobalBounds().height / 2);
}