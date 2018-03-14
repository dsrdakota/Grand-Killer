#pragma once

#include <SFML/Graphics.hpp>

#include "../../Car/Car.hpp"

class carWithWall
{
public:

	carWithWall(const carWithWall &) = delete;
	void operator=(const carWithWall &) = delete;

	inline static carWithWall& Instance()
	{
		static carWithWall carcollision;
		return carcollision;
	}

	static Hitbox::collisionSide checkCollisions(Car *car, bool react = true);

private:

	carWithWall() {}

	Car *car;

	Hitbox::collisionSide whereIsCollision();
	void collisionIs(const std::vector<sf::CircleShape*>&hitbox, const Hitbox::collisionSide &side);
	bool checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>&hitbox, bool &isCollision);
	float howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Hitbox::collisionSide &side);
	sf::Vector2f moveFromWall(const std::vector<sf::CircleShape*> &hitbox, const Hitbox::collisionSide &side);
};