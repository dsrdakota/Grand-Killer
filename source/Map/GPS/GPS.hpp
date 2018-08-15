#pragma once

#include <SFML/Graphics.hpp>

#include "../Map.hpp"
#include "../../Engine/Engine.hpp"
#include "Point.hpp"

#include <iostream>

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
	void setMission();
	void findBestRoute();
	void clear();

	std::vector<sf::RectangleShape*>&getDirections();
	std::vector<sf::CircleShape*>&getLinks();

private:

	GPS();

	std::vector<Point*>crossing;

	std::vector<sf::RectangleShape*>directions;
	std::vector<sf::CircleShape*>links;

	std::vector<Point*>bestRoad;

	IObject *player;

	Point *playerPos;
	Point *targetPos;
	Point *missionPos;

	void doRoad();

	void checkAvailablePoints(std::vector<Point*> &actualRoad, Point *endTarget, float &roadLength);

	sf::RectangleShape* createSegment(Point * start, Point * stop);

	void checkMoveablePoints(Point *point);

	sf::Vector2f getTheClosestAsphaltPosFromTarget(const sf::Vector2f &position);
	void drawGpsTexture(const sf::Color &roadColor);

	bool checkRoadBeetwen(Point *p1, Point *p2);
};