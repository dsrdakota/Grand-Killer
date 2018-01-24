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

	carCollisionWithCar() {}

	sf::Vector2f getCenterOfHitbox(const sf::CircleShape &hitbox);
};