#pragma once

#include <SFML/Graphics.hpp>

#include "../../../Car/Car.hpp"

class carDentPhysics
{
public:

	static void doDents(Car *car);

private:

	static size_t checkCollision(Car *car);
	static void doDentInCar(Car * car,const std::pair<sf::CircleShape*, std::pair<sf::Vector2f, float*>> &dent, const float &power, const size_t &index);

	static sf::Vector2f getCenterOfHitbox(const sf::CircleShape &hitbox);
};