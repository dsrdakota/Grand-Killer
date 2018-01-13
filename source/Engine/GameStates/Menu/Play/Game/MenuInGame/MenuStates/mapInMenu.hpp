#pragma once

#include <SFML/Graphics.hpp>

#include "../menuStates.hpp"
#include "../../../../../../../Manager/Button.hpp"
#include "../../../../../../../Manager/Keyboard.hpp"
#include "../../../../../../../Manager/Text.hpp"
#include "../../../../../../../Manager/Time.hpp"

class mapInMenu : public menuStates
{
public:

	mapInMenu();
	~mapInMenu();

	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	bool isActive() override;
	void drawActive() override;
	void drawUnactive() override;

	void setPlayerPosition(const sf::Vector2f &pos, const float &rot);

private:

	sf::RectangleShape *map;
	sf::Sprite *player;
	sf::Sprite *target;
	sf::Sprite *cursor; // to change !!!
	std::vector<sf::RectangleShape*>tag;

	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	sf::IntRect mapRect;
	sf::Vector2f playerPosition;
	float playerRotation;
	sf::Vector2f targetPosition;
	sf::Vector2f menuPos;

	Time time;
	int playerIsVisible;
	bool active;
	bool targetIsSet;
	bool canSetTarget;

	void toControl();
	bool mouseOnMap();
	void draw();

	void setPlayerVisible();
	void setPlayer();
	void setTarget();

};