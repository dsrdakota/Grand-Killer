#pragma once

#include "../Objects/Sign.hpp"

#include "../../Engine/Engine.hpp"

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