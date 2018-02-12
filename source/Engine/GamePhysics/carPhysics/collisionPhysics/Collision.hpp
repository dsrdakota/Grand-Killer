#pragma once

#include <SFML/Graphics.hpp>

#include "carCollisionWithWall.hpp"
#include "carCollisionWithCar.hpp"
#include "../../../GameStates/Menu/Play/Game/mGame.hpp"

class Collision
{
public:

	~Collision() { ; }

	Collision(const Collision &) = delete;
	void operator=(const Collision &) = delete;

	inline static Collision& Instance()
	{
		static Collision collision;
		return collision;
	}

	static void checkAllCarsCollision();

	static sf::Vector2f getCenterOfHitbox(const sf::CircleShape & hitbox);

	static void rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle);
	static void moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset);

private:

	Collision() { ; }

	Car::collisionSide checkCollisionCarWithWall(Car *car);
	Car::collisionSide checkCollisionCarWithCar(Car *car1, Car *car2);
	void checkCollisionCarWithHuman();
};