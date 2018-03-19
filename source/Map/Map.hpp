#pragma once

#include <SFML/Graphics.hpp>

#include "ObjectsManager/Tiles.hpp"
#include "../Engine/Engine.hpp"

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

	void init();

	std::vector<std::pair<sf::Sprite*, int*>> &getAllCarTraces() { return allCarSingleTraces; }

	sf::View* getView() { return view; }
	void setView(const sf::Vector2f &center);
	void setRotation(const float &angle);
	void updateView(const sf::Vector2f &newerView);

	void drawUnder();
	void drawOn();

	static sf::Vector2f getMapSize(){ return *Instance().mapSize; }
	static bool isOutsideView(const sf::Vector2f & pos);
	static bool isPointOnGrass(const sf::Vector2f & pos);
	static bool isPointInCollisionArea(const sf::Vector2f & pos);
	static sf::Vector2f getUpLeftCornerPosOfCurrentView();

private:
	Map();

	sf::RenderWindow *window;

	sf::Sprite *map;
	sf::Sprite *radar;

	sf::RenderTexture *textureOfMap;
	sf::RenderTexture *textureOfMiniMap;
	sf::Image *hitboxGrass;

	const sf::Vector2f *mapSize;

	Time clock;

	std::vector<std::pair<sf::Sprite*, int*>>allCarSingleTraces;

	sf::View *view;

	void updateTimeInTrace();
};