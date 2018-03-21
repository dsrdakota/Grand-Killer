#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../Engine/Engine.hpp"

#include "../../../../Map/ObjectsManager/Tiles.hpp"

#include "States/MapInMenu/mapInMenu.hpp"
#include "States/Diary/Diary.hpp"
#include "States/GameInMenu/GameInMenu.hpp"
#include "States/Statistics/Statistics.hpp"
#include "States/Steerage/Steerage.hpp"

class Menu
{
public:

	Menu();
	~Menu();

	void updateCooldown();
	void restartCooldownValue();
	void setPosition(const sf::Vector2f &playerPos, const float &playerRot);
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

	MenuStates * wsk;
	MapInMenu *map;

	std::vector<MenuStates*>options;

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