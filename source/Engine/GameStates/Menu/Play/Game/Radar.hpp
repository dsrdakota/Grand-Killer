#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../Map/Map.hpp"
#include "../../../../Player/Player.hpp"

class Radar
{
public:

	~Radar();

	Radar(const Radar &) = delete;
	void operator=(const Radar &) = delete;

	inline static Radar& Instance()
	{
		static Radar radar;
		return radar;
	}

	void update(Player *player);
	void draw();

private:

	Radar();

	sf::RenderWindow *window;

	sf::Sprite *radar;
	sf::Sprite *radarView;
	sf::Sprite *radarView2; // more opacity
	sf::RectangleShape *radarArea;

	std::vector<std::vector<Tile*>>radarTiles;

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