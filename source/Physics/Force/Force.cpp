#include "Force.hpp"

#include <iostream>

Force::Force(const sf::Vector2f &place, const sf::Vector2f &direction, const float &power)
{
	this->place = place;
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

void Force::draw(sf::RenderWindow & window)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = place;
	line[1].position = place + direction * power * 100.f;

	line[0].color = sf::Color::Blue;
	line[1].color = sf::Color::Blue;

	window.draw(line);
}
