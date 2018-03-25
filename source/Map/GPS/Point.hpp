#pragma once

#include <SFML/Graphics.hpp>

class Point
{
public:

	Point() { ; }
	Point(const sf::Vector2f &position, const sf::Vector2u &tileIndex = sf::Vector2u(0,0));

	sf::Vector2f getPointPosition();
	sf::Vector2u getTileIndex();
	std::vector<Point*>getPointsToMoveable();

	void setPosition(const sf::Vector2f &position);

	void addPointToMoveable(Point *point);
	void resetPoint();

private:

	sf::Vector2u tileIndex;
	sf::Vector2f position;
	std::vector<Point*>pointsToMoveable;
};