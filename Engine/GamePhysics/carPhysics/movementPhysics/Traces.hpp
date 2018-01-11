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

	std::vector<std::pair<std::pair<sf::Vector2f, float>, int>>tracesGrassPos;
	std::vector<std::pair<std::pair<sf::Vector2f, float>, int>>tracesAsphaltPos;

	Time clock;

	void drawOneTypeTraces(std::vector<std::pair<std::pair<sf::Vector2f, float>, int>> &tracesPos, const std::string &nameTexture);
	void updateTimeInTrace();
	bool isSameTraceOnVector(std::vector<std::pair<std::pair<sf::Vector2f, float>, int>>tracesPosVector, const sf::Vector2f &pos);

	sf::Vector2f getCenterOfHitbox(const sf::CircleShape &hitbox);
};