#pragma once
#include <SFML/Graphics.hpp>

class DoorTrailer
{
public:

	DoorTrailer(); // Trailer 3
	~DoorTrailer();
	void open(const float &angle, sf::ConvexShape &door);
	void close(const float &angle, sf::ConvexShape &door);

	sf::Sprite *center;

	sf::ConvexShape *door;

	double *angleOpen, *angleClose;

	const double *MAX_DOOR_OPEN_ANGLE;
};