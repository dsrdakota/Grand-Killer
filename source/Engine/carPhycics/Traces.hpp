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

	sf::Texture* traceGrassTexture;
	sf::Texture* traceAsphaltTexture;

	const sf::CircleShape *tiresPos;
	const std::vector<sf::CircleShape*>*tiresHitbox;
	std::vector<std::pair<sf::Sprite*,int>>traces;

	Time clock;

	void updateTimeInTrace();
	bool isSameTraceOnVector(const sf::Vector2f &pos, const float &rot);
};