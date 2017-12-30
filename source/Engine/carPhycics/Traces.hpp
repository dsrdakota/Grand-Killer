#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "../../Manager/Time.hpp"
class Car;
class Traces
{
public:
	Traces(Car *car, const sf::CircleShape *tiresPos, const std::vector<sf::CircleShape*>*tiresHitbox);
	~Traces();

	void setTraces();
	void draw();

private:

	Car *car;

	const sf::CircleShape *tiresPos;
	const std::vector<sf::CircleShape*>*tiresHitbox;

	std::vector<std::pair<std::pair<sf::Vector2f, float>, int>>tracesGrassPos;
	std::vector<std::pair<std::pair<sf::Vector2f, float>, int>>tracesAsphaltPos;

	Time clock;

	void drawOneTypeTraces(std::vector<std::pair<std::pair<sf::Vector2f, float>, int>> &tracesPos, const std::string &nameTexture);
	void updateTimeInTrace();
	bool isSameTraceOnVector(std::vector<std::pair<std::pair<sf::Vector2f, float>, int>>tracesPosVector, const sf::Vector2f &pos);
};