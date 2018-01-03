#pragma once

#include <SFML/Graphics.hpp>

class Other
{
public:

	Other();
	~Other();

	void draw();

private:

	sf::Sprite *leaves;
	sf::Sprite *roofs;
};