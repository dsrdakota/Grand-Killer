#pragma once

#include <SFML/Graphics.hpp>

#include "../Map.hpp"
#include "../../Engine/Engine.hpp"
#include "Point.hpp"

#include <thread>

class GPS
{
public:

	~GPS();

	GPS(const GPS &) = delete;
	void operator=(const GPS &) = delete;

	inline static GPS& Instance()
	{
		static GPS gps;
		return gps;
	}

	void setPlayer(IObject *player);
	void setTarget();
	void findBestRoute();

private:

	GPS();

	sf::Sprite *radarTexture;
	sf::RenderTexture *gpsTexture;

	std::vector<Point*>crossing;
	std::vector<sf::Vector2f>linkCrossing;

	std::vector<Point*>bestRoad;

	IObject *player;

	Point *playerPos;
	Point *targetPos;

	float actualRoadLength;
	bool isRoadFinded;

	void doRoad();
	void checkAvailablePoints(std::vector<Point*> &actualRoad);

	void checkMoveablePoints(Point *point);

	sf::Vector2f getTheClosestAsphaltPosFromTarget(const sf::Vector2f &position);
	void drawGpsTexture();

	bool checkRoadBeetwen(Point *p1, Point *p2);
};