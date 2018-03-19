#pragma once
#include "SFML/Graphics.hpp"

#include "../../Map/Map.hpp"

class Car;
class Traces
{
public:
	Traces(Car *car, const sf::CircleShape *tiresPos);

	void setTraces();

private:

	Car *car;

	const sf::CircleShape *tiresPos;

	bool isSameTraceOnVector(const sf::Vector2f &pos, const float &rot);
};