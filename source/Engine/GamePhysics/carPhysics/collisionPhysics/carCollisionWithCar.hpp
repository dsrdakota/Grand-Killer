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

	carCollisionWithCar() {}

	std::pair<Car::collisionSide, Car::collisionSide> whereIsCollision();
	bool checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, bool &isCollision1, bool &isCollision2);
	
	void rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle);
	void moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset);

	float howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide & side);
	sf::Vector2f moveFromCar(Car *car1, Car *car2, const std::pair<Car::collisionSide, Car::collisionSide>&side);

	bool checkCollisionWithOneHitbox(const std::pair<std::vector<sf::CircleShape*>, std::vector<sf::CircleShape*>>&hitbox, const std::pair<bool*, bool*>&isCollision);
	sf::Vector2f getCenterOfHitbox(const sf::CircleShape & hitbox);
};