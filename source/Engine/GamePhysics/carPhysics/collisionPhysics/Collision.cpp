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

bool Collision::onlyCheckCollisionCarWithWall(Car * car)
{
	Car::collisionSide side = carCollisionWithWall::checkCollisions(car,false);

	if (side == Car::collisionSide::None)
		return false;
	return true;
}

bool Collision::onlyCheckCollisionCarWithCar(Car * car1, Car * car2)
{
	Car::collisionSide side = carCollisionWithCar::checkCollisions(car1,car2,false);

	if (side == Car::collisionSide::None)
		return false;
	return true;
}

sf::Vector2f Collision::getCenterOfHitbox(const sf::CircleShape & hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}

void Collision::rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle)
{
	for (const auto &i : hitbox)
		i->rotate(angle);
}

void Collision::moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset)
{
	for (const auto &i : hitbox)
		i->move(offset);
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