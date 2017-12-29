#pragma once

#include <SFML/Graphics.hpp>

#include "MapEffects/SwimmingPool.hpp"
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
	void updateView(const sf::Vector2f &newerView);

	void drawUnder();
	void drawOn();

	static bool isOutsideView(const sf::Vector2f & pos);

	sf::Image* getGrassHitbox() { return grassHitbox; }
	sf::Image* getCollisionHitbox() { return collisionHitbox; }
	TrafficSigns* getAllTrafficSigns() { return trafficSigns; }
	TrafficLights* getAllTrafficLights() { return trafficLights; }

private:
	Map();

	sf::RenderWindow *window;
	sf::Sprite *map;

	sf::Image *grassHitbox;
	sf::Image *collisionHitbox;

	sf::View *view;

	SwimmingPool *swimmingPool;
	Other *otherElements; // leaves & roofs
	TrafficSigns *trafficSigns;
	TrafficLights *trafficLights;
};