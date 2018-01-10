#pragma once

#include "../../../../../../Game.hpp"

class menuStates
{
public:

	menuStates() : window(Game::Instance().getWindow()) {}

	virtual void setPosition(const sf::Vector2f &menuPos) = 0;
	virtual void draw() = 0;

	sf::RenderWindow *window;
};