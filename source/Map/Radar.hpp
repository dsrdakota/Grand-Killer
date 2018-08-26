#pragma once

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "../IObject/IObject.hpp"

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

	static sf::Sprite *getRadarSprite();
	void update(IObject *player);
	void draw();

private:

	Radar();

	sf::RenderWindow *window;

	sf::RenderTexture *textureOfRadar;
	sf::RenderTexture *textureOfGPS;

	sf::Sprite *radar;
	sf::Sprite *radarView;
	sf::Sprite *radarView2; // more opacity
	sf::RectangleShape *radarArea;

	sf::RectangleShape *gps;
	sf::RectangleShape *gps2; // more opacity

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
	void setGPSOnRadar();
	void drawGPSTexture();
};