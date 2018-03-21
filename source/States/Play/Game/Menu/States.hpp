#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../Game.hpp"

class MenuStates
{
public:

	MenuStates() : window(Game::Instance().getWindow()) {}

	virtual void setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) = 0;
	virtual bool exit() = 0;
	virtual bool isActive() = 0;
	virtual void drawActive() = 0;
	virtual void drawUnactive() = 0;

	sf::RenderWindow *window;
};