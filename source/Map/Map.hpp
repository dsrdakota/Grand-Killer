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

	enum class TypeOfZones
	{
		GPS
	};

	std::vector<std::pair<sf::Sprite*, int*>> &getAllCarTraces();

	static sf::Sprite *getMap();

	void drawUnder();
	void drawOn();

	static sf::Vector2f getMapSize();
	static bool isPointOnGrass(const sf::Vector2f & pos);
	static bool isPointInCollisionArea(const sf::Vector2f & pos);

	const sf::Vector2f &getZoneSize() const;
	std::vector<sf::Vector2f> &getZone(const TypeOfZones &type, const sf::Vector2i &index);

private:

	sf::Sprite *map;
	sf::Sprite *radar;

	sf::RenderTexture *textureOfMap;
	sf::RenderTexture *textureOfMiniMap;
	sf::Image *hitboxGrass;

	const sf::Vector2f *mapSize;

	sf::Vector2f zoneSize;
	std::vector<std::vector<std::unordered_map<TypeOfZones, std::vector<sf::Vector2f>>>>zones;

	Time clock;

	std::vector<std::pair<sf::Sprite*, int*>>allCarSingleTraces;

	Map();

	void updateTraces();
	void updateTimeInTrace();
	void createZones();
	void createZone(const TypeOfZones &type);
};