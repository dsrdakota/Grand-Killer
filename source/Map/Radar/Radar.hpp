#pragma once

#include <SFML/Graphics.hpp>

#include "../Map.hpp"
#include "../../IObject/IObject.hpp"
#include "../../Engine/Engine.hpp"

class Radar : public Map
{
public:

	Radar();
	~Radar();

	void update(IObject *player);
	void draw();

private:

	sf::Sprite *radarView;
	sf::Sprite *radarView2; // more opacity
	sf::RectangleShape *radarArea;

	sf::Vector2f scale;

	sf::Sprite *playerIco;
	float playerRotation;

	sf::Sprite *target;

	sf::RectangleShape *hp;
	sf::RectangleShape *hpBackground;
	sf::RectangleShape *armor;
	sf::RectangleShape *armorBackground;
	sf::RectangleShape *third; // condition or car damage
	sf::RectangleShape *thirdBackground;

	void centerMapOnPlayer();
};