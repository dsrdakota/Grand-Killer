#include "Mainmap.hpp"

std::vector<std::pair<sf::Sprite*, int*>>& Mainmap::getAllCarTraces()
{
	return allCarSingleTraces;
}

bool Mainmap::isPointOnGrass(const sf::Vector2f & point)
{
	if (point.x < 0 || point.y < 0)
		return false;

	if (point.x > size.x || point.y > size.y)
		return false;

	if (grassHitbox->getPixel(static_cast<unsigned>(point.x), static_cast<unsigned>(point.y)) == sf::Color::White)
		return true;

	return false;
}

bool Mainmap::isPointInCollisionArea(const sf::Vector2f & point)
{
	if (point.x < 0 || point.x > size.x)
		return true;
	if (point.y < 0 || point.y > size.y)
		return true;

	// buildings

	return false;
}
