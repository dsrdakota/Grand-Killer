#pragma once

#include <SFML/Graphics.hpp>

#include "../../Manager/Tiles.hpp"

#include "MapEffects/Tile.hpp"
#include "MapEffects/OtherElements.hpp"
#include "MapEffects/TrafficSigns.hpp"
#include "MapEffects/TrafficLights.hpp"

class Map
{
public:

	~Map();

	Map(const Map &) = delete;
	void operator=(const Map &) = delete;

	inline static Map& Instance()
	{
		static Map map;
		return map;
	}

	void setView(const sf::Vector2f &center);
	void setRotation(const float &angle);
	void updateView(const sf::Vector2f &newerView);

	void drawUnder();
	void drawOn();

	static bool isOutsideView(const sf::Vector2f & pos);
	static bool isPointOnGrass(const sf::Vector2f & pos);
	static bool isPointInCollisionArea(const sf::Vector2f & pos);
	static sf::Vector2f getUpLeftCornerPosOfCurrentView();

	TrafficSigns* getAllTrafficSigns() { return trafficSigns; }
	TrafficLights* getAllTrafficLights() { return trafficLights; }

private:
	Map();

	sf::RenderWindow *window;

	const sf::Vector2f *mapSize;
	const short int *TileSize;
	const short int *tilesCountWidth;
	const short int *tilesCountHeigth;

	std::vector<std::vector<Tile*>>Tiles;

	sf::View *view;

	Other *otherElements;
	TrafficSigns *trafficSigns;
	TrafficLights *trafficLights;
};