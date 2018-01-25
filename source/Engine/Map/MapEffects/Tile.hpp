#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:

	Tile(const size_t &index, const sf::Vector2f &position);
	~Tile();

	sf::Sprite *getTileSprite();
	const size_t getIndex();

	void draw();

private:

	sf::Sprite *sprite;
	size_t index;
};