#pragma once

#include <SFML/Graphics.hpp>

class MenuInGame
{
public:

	MenuInGame(const sf::Vector2u &windowSize);
	~MenuInGame();

	void draw(const sf::Vector2f &menuPos);

private:

	sf::RectangleShape *background;
};