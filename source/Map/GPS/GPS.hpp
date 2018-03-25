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

	std::vector<sf::Drawable*>&getDirections();

private:

	GPS();

	sf::Sprite *radarTexture;
	sf::RenderTexture *gpsTexture;

	sf::Vector2f zoneSize;

	std::vector<Point*>crossing;
	std::vector<std::vector<std::vector<sf::Vector2f>>>zones;

	std::vector<sf::Drawable*>directions;

	std::vector<Point*>bestRoad;

	IObject *player;

	Point *playerPos;
	Point *targetPos;

	void doRoad();
	void checkAvailablePoints(std::vector<Point*> &actualRoad, Point *endTarget, float &roadLength);
	void optimazeRoad();

	void createSegment(sf::RectangleShape *segment, Point * start, Point * stop);

	void checkMoveablePoints(Point *point);

	sf::Vector2f getTheClosestAsphaltPosFromTarget(const sf::Vector2f &position);
	void drawGpsTexture();

	bool checkRoadBeetwen(Point *p1, Point *p2);
};