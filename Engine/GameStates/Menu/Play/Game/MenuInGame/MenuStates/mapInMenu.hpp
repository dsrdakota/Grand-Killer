#pragma once

#include <SFML/Graphics.hpp>

#include "../menuStates.hpp"
#include "../../../../../../../Manager/Button.hpp"
#include "../../../../../../../Manager/Keyboard.hpp"

class mapInMenu : public menuStates
{
public:

	mapInMenu();
	~mapInMenu();

	void setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	void drawActive() override;
	void drawUnactive() override;

	void setPlayerPosition(const sf::Vector2f &pos);
	bool isActive();

private:

	sf::RectangleShape *map;
	sf::CircleShape *player; // to change

	sf::IntRect mapRect;
	sf::Vector2f playerPosition;
	bool active;

	void toControl();
	bool mouseOnMap();
	void draw();

};