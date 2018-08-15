#pragma once

#include <SFML/Graphics.hpp>

class Force
{
public:

	Force(const sf::Vector2f &direction, const float &power);

	const sf::Vector2f &getDirection() const;
	float &getPower();

private:

	sf::Vector2f place;
	sf::Vector2f direction;
	float power;
};