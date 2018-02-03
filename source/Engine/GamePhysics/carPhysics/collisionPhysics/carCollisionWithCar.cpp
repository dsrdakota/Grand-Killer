#include "carCollisionWithCar.hpp"

#include <iostream>

Car::collisionSide carCollisionWithCar::checkCollisions(Car * car1, Car * car2)
{
	if (car1 == car2)
		return Car::collisionSide::None;

	if (car1->getSprite()->getGlobalBounds().intersects(car2->getSprite()->getGlobalBounds()))
	{
		auto &instance = Instance();
		instance.car1 = car1;
		instance.car2 = car2;

		std::pair<Car::collisionSide, Car::collisionSide> carSidesOfCollision = instance.whereIsCollision();

		if (carSidesOfCollision.first == Car::collisionSide::Front)
		{
			if(car1->getStateMoving() == 0)
				car1->setSpeed(0);
			car1->getBoolIsCollision(Car::collisionSide::Front) = true;
			*car1->getLastCollisionSide() = Car::collisionSide::Front;
		}
		else if (carSidesOfCollision.first == Car::collisionSide::None)
		{
			//car1->getBoolIsCollision(Car::collisionSide::Front) = false;
			*car1->getLastCollisionSide() = Car::collisionSide::None;
		}

		return carSidesOfCollision.first;
	}

	return Car::collisionSide::None;
}

std::pair<Car::collisionSide, Car::collisionSide> carCollisionWithCar::whereIsCollision()
{
	for (auto i = 0;i < 8;++i)
		for (auto j = 0;j < 8;++j)
			if (checkCollisionBetweenTwoCars(std::make_pair(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(i)), car2->getCollisionHitbox(static_cast<Car::hitboxPosition>(j))),
				car1->getBoolIsCollision(static_cast<Car::collisionSide>(i)), car2->getBoolIsCollision(static_cast<Car::collisionSide>(j))))
				return std::make_pair(static_cast<Car::collisionSide>(i), static_cast<Car::collisionSide>(j));

	return std::make_pair(Car::collisionSide::None, Car::collisionSide::None);
}

bool carCollisionWithCar::checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, bool &isCollision1, bool &isCollision2)
{
	for (const auto &i : hitbox.first)
		for (const auto &j : hitbox.second)
			if (i->getGlobalBounds().intersects(j->getGlobalBounds()))
				return true;

	isCollision1 = false;
	isCollision2 = false;
	return false;
}