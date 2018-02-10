#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Car/Car.hpp"

class carCollisionWithWall
{
public:

	carCollisionWithWall(const carCollisionWithWall &) = delete;
	void operator=(const carCollisionWithWall &) = delete;

	inline static carCollisionWithWall& Instance()
	{
		static carCollisionWithWall carcollision;
		return carcollision;
	}

	static Car::collisionSide checkCollisions(Car *car, bool react = true);

private:

	carCollisionWithWall() {}

	Car *car;

	Car::collisionSide whereIsCollision();
	void collisionIs(const std::vector<sf::CircleShape*>&hitbox, const Car::collisionSide &side);
	bool checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>&hitbox, bool &isCollision);
	float howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide &side);
	sf::Vector2f moveFromWall(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide &side);
};