#pragma once
#include "SFML/Graphics.hpp"

#include "../../../../Manager/Time.hpp"

class Car;
class Traces
{
public:
	Traces(Car *car, const sf::CircleShape *tiresPos);

	void setTraces();
	void draw();

private:

	Car *car;

	const sf::CircleShape *tiresPos;

	std::vector<std::pair<sf::Sprite*, int>>traces;

	Time clock;

	void updateTimeInTrace();
	bool isSameTraceOnVector(std::vector<std::pair<sf::Sprite*, int>> &tracesVector, const sf::Vector2f &pos);

	sf::Vector2f getCenterOfHitbox(const sf::CircleShape &hitbox);
};