#pragma once

#include <SFML/Graphics.hpp>

#include "carType.hpp"
#include "../../Manager/Time.hpp"

class Mirror
{
public:
	
	Mirror(const carType::Type &type);
	~Mirror();

	sf::Sprite *getMirrors();

	void setPosition(const sf::ConvexShape *car, const carType::Type &type);
	void move(const sf::Vector2f &offset);
	void rotate(const double &angle);

	void checkCollision();

	void drawUnder();
	void drawOn();

private:

	sf::Sprite *mirrors;
	sf::CircleShape *hitboxes;
	bool isBroken[2];
	bool isDrawAble[2];
	int *timeOfDrawUnable;
	Time *clock;

	void setDefaultVars();

	bool isCollision(const size_t &index);
	void playAnimation(const size_t &index);
};