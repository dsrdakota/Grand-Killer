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

	static void checkAllCarCollision();

private:

	Collision();

	void checkCollisionCarWithWall(Car *car);
	void checkCollisionCarWithCar(Car *car1, Car *car2);
	void checkCollisionCarWithHuman();

	sf::Vector2f getCenterOfHitbox(const sf::CircleShape *hitbox);
};