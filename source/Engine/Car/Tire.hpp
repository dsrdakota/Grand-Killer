#pragma once

#include "SFML/Graphics.hpp"

#include "carType.hpp"

#include "../carPhysics/Traces.hpp"
class Car;
class Tire
{
public:

	Tire(Car *car,const carType::Type &type);
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
	void setPosition(const sf::ConvexShape *car,const carType::Type &type);
	void move(const sf::Vector2f &offset);
	void rotate(const double &angle, const sf::ConvexShape* car);

	void draw();

private:

	sf::Sprite *tires;

	sf::CircleShape *tiresPos;

	Traces *traces;
};