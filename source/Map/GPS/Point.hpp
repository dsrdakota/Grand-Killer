#pragma once

#include <SFML/Graphics.hpp>

class Point
{
public:
	Point(const sf::Vector2u &point, const sf::Vector2u &tileIndex);
	~Point();

	sf::Vector2u getPointPosition();
	sf::Vector2u getTileIndex();
	std::vector<Point*>getPointsToMoveable();
	sf::CircleShape *getTag();
	void addPointToMoveable(Point *point);

private:

	sf::Vector2u point;
	sf::Vector2u tileIndex;
	sf::CircleShape *shape;
	std::vector<Point*>pointsToMoveable;
};