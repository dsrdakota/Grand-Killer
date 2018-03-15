#pragma once

#include <SFML/Graphics.hpp>

#include "ObjectsManager/Tiles.hpp"
#include "../Engine/Engine.hpp"

class Map
{
public:

	Map();

	void updateMap();

	const sf::Vector2u& getSize();
	std::vector<std::vector<sf::Sprite*>>&getTiles();
	sf::Sprite* getMap();

protected:

	sf::Vector2u size;
	std::vector<std::vector<sf::Sprite*>>tiles;
	sf::RenderTexture *mapTexture;
	sf::Sprite *map;

	~Map();
};