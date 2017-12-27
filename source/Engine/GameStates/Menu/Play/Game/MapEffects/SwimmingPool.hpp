#pragma once

#include "SFML/Graphics.hpp"
#include "../../../../../../Manager/Time.hpp"

class SwimmingPool
{
public:

	SwimmingPool();
	~SwimmingPool();
	void draw();

private:

	unsigned countOfTexture;
	Time clock;

	sf::Sprite *swimmingPool;
};