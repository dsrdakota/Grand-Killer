#pragma once

#include <SFML/Graphics.hpp>

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

	sf::Image* getGrassHitbox() { return grassHitbox; }
	sf::Image* getCollisionHitbox() { return collisionHitbox; }
	TrafficSigns* getAllTrafficSigns() { return trafficSigns; }
	TrafficLights* getAllTrafficLights() { return trafficLights; }

private:
	Map();

	sf::RenderWindow *window;

	sf::Image *grassHitbox;
	sf::Image *collisionHitbox;

	std::vector<std::string>FilePath;
	std::vector<std::vector<int>>Tiles;
	std::vector<sf::Sprite*>TileSprite;

	const short int *TileSize;
	const short int *MapWidth;
	const short int *MapHeight;

	sf::View *view;

	Other *otherElements; // leaves & roofs
	TrafficSigns *trafficSigns;
	TrafficLights *trafficLights;
};