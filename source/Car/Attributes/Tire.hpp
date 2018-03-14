#pragma once

#include "SFML/Graphics.hpp"

#include "../Behaviors/Traces.hpp"

class Car;

class Tire
{
public:

	Tire(Car *car);
	~Tire();

	enum class Side
	{
		Front_left,
		Front_right,
		Back_left,
		Back_right
	};

	inline sf::Sprite* getTires(const size_t &index) { return &tires[index]; }
	inline sf::CircleShape* getTiresPos(const size_t &index) { return &tiresPos[index]; }
	void move(const sf::Vector2f &offset);
	void rotate(const double &angle);

	void setTraces();
	void draw();

private:

	sf::Sprite *tires;

	sf::CircleShape *tiresPos;

	Traces *traces;
};