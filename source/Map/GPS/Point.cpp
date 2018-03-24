#include "Point.hpp"

#include "../ObjectsManager/Tiles.hpp"

Point::Point(const sf::Vector2f & position, const sf::Vector2u &tileIndex)
{
	this->position = position;
	this->tileIndex = tileIndex;
}

sf::Vector2f Point::getPointPosition()
{
	return position;
}

sf::Vector2u Point::getTileIndex()
{
	return tileIndex;
}

std::vector<Point*> Point::getPointsToMoveable()
{
	return pointsToMoveable;
}

void Point::setPosition(const sf::Vector2f & position)
{
	this->position = position;
	tileIndex.x = position.x / static_cast<float>(TilesManager::getTileSize());
	tileIndex.y = position.y / static_cast<float>(TilesManager::getTileSize());
}

void Point::addPointToMoveable(Point *point)
{
	pointsToMoveable.push_back(point);
}

void Point::resetPoint()
{
	pointsToMoveable.clear();
}
