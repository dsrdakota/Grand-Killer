#include "TrailerStates.hpp"

TrailerStates::TrailerStates()
{
	frame = 0;

	dark = new sf::RectangleShape(sf::Vector2f(1366, 768));

	transparency = 255;

	dark->setFillColor(sf::Color(0, 0, 0, transparency));
}

TrailerStates::~TrailerStates()
{
	delete dark;
	delete backgroundImg;
}