#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:

	Tile(const size_t &index, const sf::Vector2f &position);
	~Tile();

	sf::Sprite *getTileSprite();

	void draw();

private:

	sf::Sprite *sprite;
};