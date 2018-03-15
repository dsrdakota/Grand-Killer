#pragma once

#include <SFML/Graphics.hpp>

#include "ObjectsManager/Tiles.hpp"

#include "Mainmap/Mainmap.hpp"
#include "Minimap/Minimap.hpp"
#include "Radar/Radar.hpp"

#include "../Engine/Engine.hpp"

class MapsManager
{
public:

	MapsManager(const MapsManager &) = delete;
	void operator=(const MapsManager &) = delete;

	inline static MapsManager& Instance()
	{
		static MapsManager mapsManager;
		return mapsManager;
	}

	~MapsManager();

	static Mainmap* getMainmap();
	static Minimap* getMinimap();
	static Radar* getRadar();

	void init();

private:

	MapsManager();

	Mainmap *mainmap;
	Minimap *minimap;
	Radar *radar;

	void loadMapFromFile();
	void addTile(const Tiles::Types &type, const sf::Vector2f &position);
};