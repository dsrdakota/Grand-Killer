#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../../../Game.hpp"

#include "menuStates.hpp"
#include "MenuStates/mapInMenu.hpp"

#include "../../../../../../Manager/Time.hpp"
#include "../../../../../../Manager/Text.hpp"
#include "../../../../../../Manager/Button.hpp"

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

	enum class States
	{
		Map,
		Dziennik,
		Statystyki,
		Settings,
		Game,
	};

private:

	sf::RenderWindow *window;

	States *state;

	menuStates * wsk;
	mapInMenu *map;

	Time timeEscapeButton;
	Time timeChangeStates;
	Text *grandKillerText;

	sf::Sprite *leftArrow;
	sf::Sprite *rightArrow;

	int cooldownEscapeButton;
	int cooldownChangeStates;

	sf::RectangleShape *background;

	std::vector<Button *>headersButton;

	void update();
	void checkArrowIsPressed(const int &side);
	bool mouseOnClickArrow(sf::Sprite *arrow);
	bool mouseOnArrow(sf::Sprite *arrow);
};