#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Car/Car.hpp"

class carCollisionWithCar
{
public:

	carCollisionWithCar(const carCollisionWithCar &) = delete;
	void operator=(const carCollisionWithCar &) = delete;

	inline static carCollisionWithCar& Instance()
	{
		static carCollisionWithCar carcollision;
		return carcollision;
	}

	static Car::collisionSide checkCollisions(Car *car1, Car *car2, bool react = true);

private:

	Car * car1;
	Car * car2;

	float speed;

	float powerFirst;
	float powerSecond;

	carCollisionWithCar() {}

	std::pair<Car::collisionSide, Car::collisionSide> whereIsCollision();
	bool checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, const std::pair<bool*, bool*>&isCollision);

	float howManyRotate(Car *car1, Car *car2, const std::pair<Car::collisionSide, Car::collisionSide>&side);
	sf::Vector2f moveFromCar(Car *car1, Car *car2, const std::pair<Car::collisionSide, Car::collisionSide>&side);

	void collisionIs(Car *car1, Car *car2, const std::pair<Car::collisionSide, Car::collisionSide>&side);
};