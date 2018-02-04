#pragma once

#include <SFML/Graphics.hpp>

#include "carCollisionWithWall.hpp"
#include "carCollisionWithCar.hpp"
#include "../../../GameStates/Menu/Play/Game/mGame.hpp"

class Collision
{
public:

	~Collision();

	Collision(const Collision &) = delete;
	void operator=(const Collision &) = delete;

	inline static Collision& Instance()
	{
		static Collision collision;
		return collision;
	}

	static void checkAllCarsCollision(); // checking all cars

	static bool onlyCheckCollisionCarWithWall(Car *car);
	static bool onlyCheckCollisionCarWithCar(Car *car1, Car *car2);

private:

	Collision();

	Car::collisionSide checkCollisionCarWithWall(Car *car);
	Car::collisionSide checkCollisionCarWithCar(Car *car1, Car *car2);
	void checkCollisionCarWithHuman();

	sf::Vector2f getCenterOfHitbox(const sf::CircleShape *hitbox);
};