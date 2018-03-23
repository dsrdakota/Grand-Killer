#include "Point.hpp"

Point::Point(const sf::Vector2f & point, const sf::Vector2u &tileIndex)
{
	this->point = point;
	this->tileIndex = tileIndex;

	shape = new sf::CircleShape(10);
	shape->setOrigin(10, 10);
	shape->setFillColor(sf::Color::Red);
	shape->setPosition(static_cast<sf::Vector2f>(point));
}

Point::~Point()
{
	delete shape;
	
	for (const auto &i : pointsToMoveable)
		delete i;
}

sf::Vector2f Point::getPointPosition()
{
	return point;
}

sf::Vector2u Point::getTileIndex()
{
	return tileIndex;
}

std::vector<Point*> Point::getPointsToMoveable()
{
	return pointsToMoveable;
}

sf::CircleShape * Point::getTag()
{
	return shape;
}

void Point::addPointToMoveable(Point *point)
{
	pointsToMoveable.push_back(point);
}
