#pragma once

#include <SFML/Graphics.hpp>

#include "../menuStates.hpp"
#include "../../../../../../../Manager/Button.hpp"
#include "../../../../../../../Manager/Keyboard.hpp"
#include "../../../../../../../Manager/Text.hpp"

class mapInMenu : public menuStates
{
public:

	mapInMenu();
	~mapInMenu();

	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	void drawActive() override;
	void drawUnactive() override;

	void setPlayerPosition(const sf::Vector2f &pos);
	bool isActive();

private:

	sf::RectangleShape *map;
	sf::CircleShape *player; // to change
	sf::RectangleShape *target; // to change
	sf::Sprite *cursor; // to change !!!
	std::vector<sf::RectangleShape*>tag;

	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	sf::IntRect mapRect;
	sf::Vector2f playerPosition;
	sf::Vector2f targetPosition;
	sf::Vector2f menuPos;
	bool active;
	bool targetIsSet;
	bool canSetTarget;

	void toControl();
	bool mouseOnMap();
	void draw();

	void setPlayer();
	void setTarget();

};