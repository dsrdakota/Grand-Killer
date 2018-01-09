#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../../../Manager/Time.hpp"

class MenuInGame
{
public:

	MenuInGame(const sf::Vector2u &windowSize);
	~MenuInGame();

	void updateCooldown();
	void restartCooldownValue();
	void setPosition(const sf::Vector2f &menuPos);
	const int &getCooldownValue();
	void draw();

private:

	Time time;

	int cooldown; // cooldown press button

	sf::RectangleShape *background;
};