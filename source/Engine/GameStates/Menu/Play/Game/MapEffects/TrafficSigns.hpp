#pragma once

#include "Sign.hpp"

class TrafficSigns
{
public:

	TrafficSigns();
	~TrafficSigns();

	std::vector<sf::CircleShape*> getAllSignsHitbox();

	void drawUnder();
	void drawOn();

private:

	Sign *signs;
};