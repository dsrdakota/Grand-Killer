#pragma once

#include "SFML/Graphics.hpp"

#include "carType.hpp"

#include "../carPhycics/Traces.hpp"
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
	inline sf::CircleShape *getAllTiresPos() { return tiresPos; }
	std::pair<std::vector<sf::CircleShape*>, std::vector<sf::CircleShape*>> getPairTireHitboxFront();
	std::vector<sf::CircleShape*>* getVectorTireHitbox();
	void setPosition(const sf::ConvexShape *car,const carType::Type &type);
	void moveOne(const size_t &index, const sf::Vector2f &offset);
	void move(const sf::Vector2f &offset);
	void rotate(const double &angle, const sf::ConvexShape* car);

	void draw();

	void setRotation(sf::Sprite *target, const sf::Vector2f &posTarget, const float &angle, const sf::Vector2f &origin);

private:

	sf::Sprite *tires;

	sf::CircleShape *tiresPos;

	std::vector<sf::CircleShape*>*tiresHitbox;

	Traces *traces;

	void updateHitboxPosition();

};