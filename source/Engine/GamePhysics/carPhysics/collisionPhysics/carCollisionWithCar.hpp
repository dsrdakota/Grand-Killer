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

	static void checkCollisions(Car *car1, Car *car2);

private:

	Car * car1;
	Car * car2;

	carCollisionWithCar() {}

	std::pair<Car::collisionSide, Car::collisionSide> whereIsCollision();
	bool checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, std::pair<bool*,bool*> isCollision);
};