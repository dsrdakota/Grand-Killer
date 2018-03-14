#pragma once

#include "../Map.hpp"

class Mainmap : public Map
{
public:

	std::vector<std::pair<sf::Sprite*, int*>> &getAllCarTraces();

	bool isPointOnGrass(const sf::Vector2f &point);
	bool isPointInCollisionArea(const sf::Vector2f &point);

private:

	sf::Image *grassHitbox;

	std::vector<std::pair<sf::Sprite*, int*>>allCarSingleTraces;
	
};