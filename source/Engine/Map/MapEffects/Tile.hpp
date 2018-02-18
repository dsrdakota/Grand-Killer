#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:

	Tile(const size_t &index, const sf::Vector2f &position);
	~Tile();

	sf::Sprite *getTileSprite();
	sf::Sprite *getTileMapSprite();
	sf::Sprite *getTileRadarSprite();
	const size_t getIndex();

private:

	sf::Sprite *sprite;
	sf::Sprite *mapSprite;
	sf::Sprite *radarSprite;
	size_t index;
};