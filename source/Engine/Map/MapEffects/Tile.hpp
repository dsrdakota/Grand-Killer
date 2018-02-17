#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:

	Tile(const size_t &index, const sf::Vector2f &position);
	~Tile();

	sf::Sprite *getTileSprite();
	sf::Sprite *getTileMapSprite();
	const size_t getIndex();

private:

	sf::Sprite *sprite;
	sf::Sprite *mapSprite;
	size_t index;
};