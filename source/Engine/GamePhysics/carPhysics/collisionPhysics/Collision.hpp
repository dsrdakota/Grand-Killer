#pragma once

#include <SFML/Graphics.hpp>
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
	void checkCollisionCarWithCar();
	void checkCollisionCarWithHuman();

	sf::Vector2f getCenterOfHitbox(const sf::CircleShape *hitbox);
};