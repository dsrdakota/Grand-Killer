#pragma once

#include <SFML/Graphics.hpp>

#include "../Map.hpp"
#include "../../Engine/Engine.hpp"
#include "Point.hpp"

class GPS
{
public:

	GPS(const GPS &) = delete;
	void operator=(const GPS &) = delete;

	inline static GPS& Instance()
	{
		static GPS gps;
		return gps;
	}

	void draw();
	void findBestRoute();

private:

	GPS();

	sf::Sprite *radarTexture;
	sf::RenderTexture *gpsTexture;

	std::vector<Point*>crossing;

	void setAllPointsToMoveable(Point *point);
	void getTheClosestAsphaltTileFromTarget(const sf::Vector2f &position);

	bool checkRoadBeetwen(Point *p1, Point *p2);
};