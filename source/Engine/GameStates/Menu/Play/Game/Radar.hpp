#pragma once

#include <SFML/Graphics.hpp>

#include "../../../../Map/Map.hpp"

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

	void update(const sf::Vector2f &position, const float &rotation);
	void draw();

private:

	Radar();

	sf::RenderWindow *window;

	sf::Sprite *radar;
	sf::RectangleShape *radarArea;

	std::vector<std::vector<Tile*>>radarTiles;

	sf::Vector2f scale;

	sf::Sprite *player;
	Tile *playerTile;
	sf::Vector2f lengthPlayerFromTileOrigin;
	float playerRotation;

	sf::Sprite *target;
	Tile *targetTile;
	sf::Vector2f lengthTargetFromTileOrigin;

	void centerMapOnPlayer();
	void moveAllTiles(const sf::Vector2f & offset);
};