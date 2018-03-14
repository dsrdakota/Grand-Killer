#include "Map.hpp"

#include "../Engine/Engine.hpp"
#include "MapsManager.hpp"

#include <iostream>

Map::Map()
{
	size = sf::Vector2u(6000, 6000);
	map = new sf::Sprite;
	mapTexture = new sf::RenderTexture();
	mapTexture->create(size.x, size.y);

	for (size_t i = 0; i < Tiles::getTilesCount().y; ++i)
	{
		std::vector<sf::Sprite*>buf;
		for (size_t j = 0; j < Tiles::getTilesCount().x; ++j)
			buf.push_back(new sf::Sprite());

		tiles.push_back(buf);
	}
}

Map::~Map()
{
	for (const auto &i : tiles)
		for (const auto &j : i)
			delete j;

	delete map;
	delete mapTexture;
}

std::vector<std::vector<sf::Sprite*>>& Map::getTiles()
{
	return tiles;
}

sf::Sprite * Map::getMap()
{
	return map;
}

void Map::updateMap()
{
	mapTexture->clear(sf::Color::White);
	for (const auto &i : tiles)
		for (const auto &j : i)
			mapTexture->draw(*j);

	mapTexture->display();

	map->setTexture(mapTexture->getTexture());
}