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

	void findBestRoute();

private:

	GPS();

	sf::Sprite *radarTexture;
	sf::RenderTexture *gpsTexture;

	std::vector<Point*>crossing;

	sf::Vector2f targetPos;
	sf::Vector2f playerPos;

	void setAllPointsToMoveable(Point *point);

	sf::Vector2f getTheClosestAsphaltPosFromTarget(const sf::Vector2f &position);
	void drawGpsTexture();

	bool checkRoadBeetwen(Point *p1, Point *p2);
};