#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../Engine/Engine.hpp"

#include "States/MapInMenu/mapInMenu.hpp"
#include "States/Diary/Diary.hpp"
#include "States/GameInMenu/GameInMenu.hpp"
#include "States/Statistics/Statistics.hpp"
#include "States/Steerage/Steerage.hpp"

#include "../../../../Map/MapsManager.hpp"

class MenuInGame
{
public:

	MenuInGame();
	~MenuInGame();

	void updateCooldown();
	void restartCooldownValue();
	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &playerPos, const float &playerRot);
	const int &getCooldownValue();
	bool canExitMenu();
	void draw();

	const bool isTargetSet();
	const sf::Vector2f getTargetPos();

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

	Text *name;
	Text *time;
	Text *cash;

	sf::Vector2f playerPos;
	float playerRot;

	int cooldownEscapeButton;
	int cooldownChangeStates;

	bool escapeWasRelased;
	bool optionIsActive;

	sf::RectangleShape *background;

	std::vector<Button *>headersButton;
	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	void update();
	std::string updateTime();
	void checkArrowIsPressed(const int &side);
	bool mouseOnClickArrow(sf::Sprite *arrow);
	bool mouseOnArrow(sf::Sprite *arrow);
};