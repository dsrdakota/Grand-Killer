#include "Force.hpp"

#include <iostream>

Force::Force(const sf::Vector2f &direction, const float &power)
{
	this->direction = direction;
	this->power = power;
}

const sf::Vector2f & Force::getDirection() const
{
	return direction;
}

float & Force::getPower()
{
	return power;
}
