#pragma once

#include <SFML/Graphics.hpp>

#include "../../Manager/Tiles.hpp"

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

	std::vector<std::pair<sf::Sprite*, int*>> &getAllCarTraces() { return allCarSingleTraces; }

	void setView(const sf::Vector2f &center);
	void setRotation(const float &angle);
	void updateView(const sf::Vector2f &newerView);

	void drawUnder();
	void drawOn();

	static sf::Sprite* getRadar();

	static const sf::Vector2f getMapSize() { return *Instance().mapSize; }
	static const short int getTileSize() { return *Instance().TileSize; }
	static const sf::Vector2f getCountTile() { return sf::Vector2f(*Instance().tilesCountWidth, *Instance().tilesCountHeigth); }
	static bool isOutsideView(const sf::Vector2f & pos);
	static bool isPointOnGrass(const sf::Vector2f & pos);
	static bool isPointInCollisionArea(const sf::Vector2f & pos);
	static sf::Vector2f getUpLeftCornerPosOfCurrentView();

	TrafficSigns* getAllTrafficSigns() { return trafficSigns; }
	TrafficLights* getAllTrafficLights() { return trafficLights; }

	static std::vector<std::vector<Tile*>> &getTilesVector() { return Instance().Tiles; }

private:
	Map();

	sf::RenderWindow *window;

	sf::Sprite *map;
	sf::Sprite *radar;

	sf::RenderTexture *textureOfMap;
	sf::RenderTexture *textureOfMiniMap;
	sf::Image *hitboxGrass;

	const sf::Vector2f *mapSize;
	const short int *TileSize;
	const short int *tilesCountWidth;
	const short int *tilesCountHeigth;

	Time clock;

	std::vector<std::vector<Tile*>>Tiles;
	std::vector<std::pair<sf::Sprite*, int*>>allCarSingleTraces;

	sf::View *view;

	Other *otherElements;
	TrafficSigns *trafficSigns;
	TrafficLights *trafficLights;

	void updateTimeInTrace();
};