#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../../../Game.hpp"

#include "menuStates.hpp"
#include "MenuStates/mapInMenu.hpp"
#include "MenuStates/Steerage.hpp"
#include "MenuStates/gameInMenu.hpp"
#include "MenuStates/Statistics.hpp"
#include "MenuStates/Diary.hpp"

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
	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &playerPos);
	const int &getCooldownValue();
	bool canExitMenu();
	void draw();

	enum class States
	{
		Mapa,
		Dziennik,
		Statystyki,
		Sterowanie,
		Gra,
	};

private:

	sf::RenderWindow *window;

	States *state;

	menuStates * wsk;
	mapInMenu *map;

	std::vector<menuStates*>options;

	Time timeEscapeButton;
	Time timeChangeStates;
	Text *grandKillerText;

	sf::Sprite *leftArrow;
	sf::Sprite *rightArrow;

	sf::Vector2f playerPos;

	int cooldownEscapeButton;
	int cooldownChangeStates;

	bool escapeWasRelased;
	bool optionsAreActive;
	bool mapActive;

	sf::RectangleShape *background;

	std::vector<Button *>headersButton;
	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	void update();
	void checkArrowIsPressed(const int &side);
	bool mouseOnClickArrow(sf::Sprite *arrow);
	bool mouseOnArrow(sf::Sprite *arrow);
};