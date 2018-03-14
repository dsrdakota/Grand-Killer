#pragma once

#include <SFML/Graphics.hpp>
#include "../../Car/Car.hpp"

#include "../../Car/Attributes/Hitbox.hpp"

class carWithCar
{
public:

	carWithCar(const carWithCar &) = delete;
	void operator=(const carWithCar &) = delete;

	inline static carWithCar& Instance()
	{
		static carWithCar carcollision;
		return carcollision;
	}

	static Hitbox::collisionSide checkCollisions(Car *car1, Car *car2, bool react = true);

private:

	Car * car1;
	Car * car2;

	float speed;

	float powerFirst;
	float powerSecond;

	carWithCar() {}

	std::pair<Hitbox::collisionSide, Hitbox::collisionSide> whereIsCollision();
	bool checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, const std::pair<bool*, bool*>&isCollision);

	float howManyRotate(Car *car1, Car *car2, const std::pair<Hitbox::collisionSide, Hitbox::collisionSide>&side);
	sf::Vector2f moveFromCar(Car *car1, Car *car2, const std::pair<Hitbox::collisionSide, Hitbox::collisionSide>&side);

	void collisionIs(Car *car1, Car *car2, const std::pair<Hitbox::collisionSide, Hitbox::collisionSide>&side);
};