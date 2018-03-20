#include "Map.hpp"

#include "../Game.hpp"

#include <fstream>

Map::Map()
{
	mapSize = new sf::Vector2f(6000, 6000);

	textureOfMap = new sf::RenderTexture;

	sf::RenderTexture textureOfHitboxGrass;

	textureOfMap->create(static_cast<unsigned>(mapSize->x), static_cast<unsigned>(mapSize->y));
	textureOfHitboxGrass.create(static_cast<unsigned>(mapSize->x), static_cast<unsigned>(mapSize->y));

	auto mapTiles = TilesManager::getTileMapVector();
	auto grassHitboxTiles = TilesManager::getTileHitboxGrassVector();

	textureOfMap->clear();
	textureOfHitboxGrass.clear();

	for (int i = 0; i< TilesManager::getCountTile().y; i++)
	{
		for (int j = 0; j < TilesManager::getCountTile().x; j++)
		{
			textureOfMap->draw(*mapTiles[i][j]);

			textureOfHitboxGrass.draw(*grassHitboxTiles[i][j]);
		}
	}

	textureOfMap->display();
	textureOfHitboxGrass.display();

	map = new sf::Sprite(textureOfMap->getTexture());
	hitboxGrass = new sf::Image(textureOfHitboxGrass.getTexture().copyToImage());
}

Map::~Map()
{
	delete map;
	delete textureOfMap;
	delete hitboxGrass;
}

std::vector<std::pair<sf::Sprite*, int*>>& Map::getAllCarTraces()
{
	return allCarSingleTraces;
}

sf::Sprite * Map::getMap()
{
	return Instance().map;
}

void Map::drawUnder()
{
	Painter::Instance().addToDraw(map);

	if (allCarSingleTraces.size() > 600 * allCarSingleTraces.size())
	{
		for (auto i = 0;i < 10;++i)
		{
			delete allCarSingleTraces[i].first;
			delete allCarSingleTraces[i].second;
		}

		allCarSingleTraces.erase(allCarSingleTraces.begin(), allCarSingleTraces.begin() + 10);
	}

	for (size_t i = 0;i<allCarSingleTraces.size();i++)
	{
		if (*allCarSingleTraces[i].second <= 0 &&
			Camera::isOutsideView(sf::Vector2f(allCarSingleTraces[i].first->getGlobalBounds().left + allCarSingleTraces[i].first->getGlobalBounds().width,
				allCarSingleTraces[i].first->getGlobalBounds().top + allCarSingleTraces[i].first->getGlobalBounds().height)))
		{
			delete allCarSingleTraces[i].first;
			delete allCarSingleTraces[i].second;
			allCarSingleTraces.erase(allCarSingleTraces.begin() + i, allCarSingleTraces.begin() + i + 1);
			--i;
		}
		else if (!Camera::isOutsideView(sf::Vector2f(allCarSingleTraces[i].first->getGlobalBounds().left + allCarSingleTraces[i].first->getGlobalBounds().width,
			allCarSingleTraces[i].first->getGlobalBounds().top + allCarSingleTraces[i].first->getGlobalBounds().height)))

			Painter::Instance().addToDraw(allCarSingleTraces[i].first);
	}

	updateTimeInTrace();
}

void Map::drawOn()
{
	
}

sf::Vector2f Map::getMapSize()
{
	return *Instance().mapSize;
}

bool Map::isPointOnGrass(const sf::Vector2f & pos)
{
	if (pos.x < 0 || pos.y < 0)
		return false;

	if (pos.x > Instance().mapSize->x || pos.y > Instance().mapSize->y)
		return false;

	if (Instance().hitboxGrass->getPixel(static_cast<unsigned>(pos.x), static_cast<unsigned>(pos.y)) == sf::Color::White)
		return true;

	return false;
}

bool Map::isPointInCollisionArea(const sf::Vector2f & pos)
{
	auto &map = Instance();
	if (pos.x < 0 || pos.x > map.mapSize->x)
		return true;
	if (pos.y < 0 || pos.y > map.mapSize->y)
		return true;

	// buildings

	return false;
}

void Map::updateTimeInTrace()
{
	auto &traces = Map::Instance().getAllCarTraces();

	if (clock.time->asSeconds() > 1)
	{
		for (auto &i : traces)
			if (*i.second > 0)
				(*i.second)--;

		clock.clock->restart();
		*clock.time = clock.time->Zero;
	}
}