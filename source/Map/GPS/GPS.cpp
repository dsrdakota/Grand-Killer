#include "GPS.hpp"
#include "../../States/Play/Game/mGame.hpp"

#include "../Minimap.hpp"
#include "../Radar.hpp"

#include "../ObjectsManager/MinimapIcons.hpp"

#include <iostream>
#include <fstream>

#define M_PI 3.14159265359

GPS::GPS()
{
	auto &tiles = TilesManager::getTilesVector();

	std::ifstream file("data/Map/Tileset/GPS.txt");

	sf::Vector2u point;
	while (file >> point.x >> point.y)
		crossing.push_back(new Point(sf::Vector2f(
			tiles[point.y][point.x]->getTileMapSprite()->getPosition().x + TilesManager::getTileSize() / 2.f,
			tiles[point.y][point.x]->getTileMapSprite()->getPosition().y + TilesManager::getTileSize() / 2.f
		), point));

	for (const auto &i : crossing)
		checkMoveablePoints(i);

	std::vector<Point*>linkedPoints;
	std::vector<sf::Vector2f > linkCrossing;

	for (auto &i : crossing)
	{
		if (std::find(linkedPoints.begin(), linkedPoints.end(), i) == linkedPoints.end())
		{
			for (auto &j : i->getPointsToMoveable())
			{
				if (i->getPointPosition().x == j->getPointPosition().x)
				{
					if (i->getPointPosition().y > j->getPointPosition().y)
						for (float k = i->getPointPosition().y; k > j->getPointPosition().y;k -= static_cast<float>(TilesManager::getTileSize()))
							linkCrossing.push_back(sf::Vector2f(i->getPointPosition().x, k));
					else
						for (float k = i->getPointPosition().y; k < j->getPointPosition().y;k += static_cast<float>(TilesManager::getTileSize()))
							linkCrossing.push_back(sf::Vector2f(i->getPointPosition().x, k));
				}
				else
				{
					if (i->getPointPosition().x > j->getPointPosition().x)
						for (float k = i->getPointPosition().x; k > j->getPointPosition().x;k -= static_cast<float>(TilesManager::getTileSize()))
							linkCrossing.push_back(sf::Vector2f(k, i->getPointPosition().y));

					else
						for (float k = i->getPointPosition().x; k < j->getPointPosition().x;k += static_cast<float>(TilesManager::getTileSize()))
							linkCrossing.push_back(sf::Vector2f(k, i->getPointPosition().y));
				}
			}
			linkedPoints.push_back(i);
		}
	}

	for (const auto &i : linkCrossing)
		Map::Instance().getZone(Map::TypeOfZones::GPS, sf::Vector2i(i.y / Map::Instance().getZoneSize().y, i.x / Map::Instance().getZoneSize().x)).push_back(i);

	playerPos = new Point(sf::Vector2f(0, 0));
	targetPos = new Point(sf::Vector2f(0, 0));
	missionPos = new Point(sf::Vector2f(0, 0));
}

GPS::~GPS()
{
	for (const auto &i : crossing)
		delete i;
	crossing.clear();

	for (const auto &i : directions)
		delete i;
	directions.clear();

	for (const auto &i : links)
		delete i;
	links.clear();

	delete playerPos;
	delete targetPos;
	delete missionPos;
}

void GPS::setPlayer(IObject * player)
{
	this->player = player;
}

void GPS::setTarget()
{
	auto targetTile = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Target]->getTile();

	targetPos->resetPoint();
	targetPos->setPosition(getTheClosestAsphaltPosFromTarget(targetTile->getTileMapSprite()->getPosition()));

	for (const auto &i : crossing)
		if (checkRoadBeetwen(targetPos, i))
			targetPos->addPointToMoveable(i);
}

void GPS::setMissionTarget()
{
	auto targetTile = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::MissionTarget]->getTile();

	missionPos->resetPoint();
	missionPos->setPosition(getTheClosestAsphaltPosFromTarget(targetTile->getTileMapSprite()->getPosition()));

	for (const auto &i : crossing)
		if (checkRoadBeetwen(missionPos, i))
			missionPos->addPointToMoveable(i);
}

void GPS::findBestRoutes()
{
	if(shouldFind())
	{
		clear();

		playerPos->setPosition(getTheClosestAsphaltPosFromTarget(player->getPosition()));

		if (targetPos->getPointPosition() == playerPos->getPointPosition() &&
			mGame::Instance().getGameState() == mGame::state::MainGame)
			Minimap::Instance().targetIsSet = false;

		if (missionPos->getPointPosition() == playerPos->getPointPosition() &&
			mGame::Instance().getGameState() == mGame::state::MainGame)
			Minimap::Instance().missionTargetIsSet = false;

		if (Minimap::Instance().missionTargetIsSet || Minimap::Instance().targetIsSet)
		{
			playerPos->resetPoint();

			for (const auto &i : crossing)
				if (checkRoadBeetwen(playerPos, i))
					playerPos->addPointToMoveable(i);
		}

		if (Minimap::Instance().targetIsSet)
		{
			doRoad(bestRoadToTarget, playerPos, targetPos);
			drawGpsTexture(bestRoadToTarget, targetPos->getPointPosition(), sf::Color(164, 76, 242));
			//clear();
		}

		if (Minimap::Instance().missionTargetIsSet)
		{
			doRoad(bestRoadToMissionTarget, playerPos, missionPos);
			drawGpsTexture(bestRoadToMissionTarget, missionPos->getPointPosition(), sf::Color(255, 255, 0));
			//clear();
		}
	}
}

void GPS::clear()
{
	for (const auto &i : directions)
		delete i;
	for (const auto &i : links)
		delete i;

	directions.clear();
	links.clear();
}

const std::vector<sf::RectangleShape*>& GPS::getDirections()
{
	return directions;
}

const std::vector<sf::CircleShape*>& GPS::getLinks()
{
	return links;
}

bool GPS::shouldFind()
{
	auto target = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Target]->getSprite();

	if (Minimap::Instance().isTargetSet() && Minimap::Instance().map->getGlobalBounds().contains(target->getPosition()))
		return true;

	auto mission = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::MissionTarget]->getSprite();

	if (Minimap::Instance().missionTargetIsSet)
		return true;

	return false;
}

void GPS::doRoad(std::vector<Point*> &actualRoad, Point *start, Point *stop)
{
	actualRoad.clear();
	
	std::vector<Point*> roadFromStart;
	std::vector<Point*> roadFromStop;

	float roadLengthFromStart = -1;
	float roadLengthFromStop = -1;

	roadFromStart.push_back(start);
	roadFromStop.push_back(stop);

	if (checkRoadBeetwen(start, stop))
	{
		actualRoad.push_back(start);
		actualRoad.push_back(stop);
		return;
	}

	checkAvailablePoints(roadFromStart, stop, roadLengthFromStart);
	checkAvailablePoints(roadFromStop, start, roadLengthFromStop);

	if (roadLengthFromStart < roadLengthFromStop)
		actualRoad = roadFromStart;
	else
		actualRoad = roadFromStop;
}

void GPS::checkAvailablePoints(std::vector<Point*> &actualRoad, Point *endTarget, float &roadLength)
{
	std::vector<Point*> savedRoadToTarget;

	while (std::find(savedRoadToTarget.begin(), savedRoadToTarget.end(), endTarget) == savedRoadToTarget.end())
	{
		Point* point = nullptr;
		float smallestLength = -1.f;

		for (const auto &i : actualRoad[actualRoad.size() - 1]->getPointsToMoveable())
		{
			if (std::find(actualRoad.begin(), actualRoad.end(), i) != actualRoad.end())
				continue;

			if (checkRoadBeetwen(endTarget, i))
			{
				actualRoad.push_back(i);
				actualRoad.push_back(endTarget);

				float length = 0;
				for (size_t i = 0; i < actualRoad.size() - 1; ++i)
				{
					sf::Vector2f len = actualRoad[i]->getPointPosition() - actualRoad[i + 1]->getPointPosition();
					length += sqrt(len.x * len.x + len.y *len.y);
				}

				if (roadLength == -1 ||
					roadLength > length)
				{
					roadLength = length;
					savedRoadToTarget = actualRoad;
				}

				actualRoad.pop_back();
				actualRoad.pop_back();

				continue;
			}

			sf::Vector2f vector = endTarget->getPointPosition() - i->getPointPosition();
			float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);

			if (lenght < smallestLength ||
				smallestLength == -1.f)
			{
				smallestLength = lenght;
				point = i;
			}
		}

		if (std::find(actualRoad.begin(), actualRoad.end(), endTarget) == actualRoad.end() && point)
			actualRoad.push_back(point);
	}
	actualRoad = savedRoadToTarget;
}

sf::RectangleShape* GPS::createSegment(Point * start, Point * stop)
{
	sf::RectangleShape *segment = new sf::RectangleShape;

	if (start->getPointPosition().x == stop->getPointPosition().x)
	{
		segment->setSize(sf::Vector2f(200 , start->getPointPosition().y - stop->getPointPosition().y));
		segment->setOrigin(100, 0);
		segment->setPosition(start->getPointPosition());
	}
	else // y is the same
	{
		segment->setSize(sf::Vector2f(start->getPointPosition().x - stop->getPointPosition().x, 200));
		segment->setOrigin(0, 100);
		segment->setPosition(start->getPointPosition());
	}

	segment->setRotation(180);
	return segment;
}

void GPS::checkMoveablePoints(Point * point)
{
	for (const auto &i : crossing)
		if (checkRoadBeetwen(point, i))
			point->addPointToMoveable(i);
}

sf::Vector2f GPS::getTheClosestAsphaltPosFromTarget(const sf::Vector2f & position)
{
	float smallestLength = -1.f;
	sf::Vector2f pos = sf::Vector2f(0, 0);

	std::vector<sf::Vector2f>closestZone;
	float lengthFromZone = -1.f;

	closestZone = Map::Instance().getZone(Map::TypeOfZones::GPS,sf::Vector2i(position.y / Map::Instance().getZoneSize().y, position.x / Map::Instance().getZoneSize().x));

	if (closestZone.size() < 1)
	{
		std::vector<sf::Vector2f>ZonesPosition;

		for (size_t i = 0;i < Map::getMapSize().y; i += Map::Instance().getZoneSize().y)
			for (size_t j = 0;j < Map::getMapSize().x; j += Map::Instance().getZoneSize().x)
				ZonesPosition.push_back(sf::Vector2f(i, j));

		for (const auto &i : ZonesPosition)
		{
			sf::Vector2f vector = position - i;
			float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);

			if (Map::Instance().getZone(Map::TypeOfZones::GPS, sf::Vector2i(i.y / Map::Instance().getZoneSize().y, i.x / Map::Instance().getZoneSize().x)).size() > 0 &&
				(lenght < lengthFromZone ||
					lengthFromZone == -1.f))
			{
				lengthFromZone = lenght;
				closestZone = Map::Instance().getZone(Map::TypeOfZones::GPS, sf::Vector2i(i.y / Map::Instance().getZoneSize().y, i.x / Map::Instance().getZoneSize().x));
			}
		}
	}

	for (const auto &i : closestZone)
	{
		sf::Vector2f vector = position - i;
		float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);

		if (lenght < smallestLength ||
			smallestLength == -1.f)
		{
			smallestLength = lenght;
			pos = i;
		}
	}

	return pos;
}

void GPS::drawGpsTexture(std::vector<Point*> &actualRoad, const sf::Vector2f &targetPosition, const sf::Color &roadColor)
{
	auto createLink = [&](const sf::Vector2f &position) {
		sf::CircleShape *point = new sf::CircleShape(100);
		point->setOrigin(point->getRadius(), point->getRadius());
		point->setFillColor(roadColor);
		point->setPosition(position);
		links.push_back(point);
	};

	createLink(targetPosition);

	for (size_t i = 0;i < actualRoad.size() - 1;++i)
	{
		sf::RectangleShape *roadSegment = createSegment(actualRoad[i], actualRoad[i + 1]);
	
		for (size_t j = 0;j < 2;++j)
			createLink(actualRoad[i]->getPointPosition());

		roadSegment->setFillColor(roadColor);
		directions.push_back(roadSegment);
	}
}

bool GPS::checkRoadBeetwen(Point * p1, Point * p2)
{
	if (p1->getPointPosition() == p2->getPointPosition())
		return false;

	auto &tiles = TilesManager::getTilesVector();

	if ((p1->getPointPosition().x == p2->getPointPosition().x &&
		p1->getPointPosition().y != p2->getPointPosition().y) ||
		(p1->getPointPosition().x != p2->getPointPosition().x &&
			p1->getPointPosition().y == p2->getPointPosition().y))
	{
		if (p1->getPointPosition().x == p2->getPointPosition().x)
		{
			Point *higher = p1->getPointPosition().y < p2->getPointPosition().y ? p2 : p1;
			Point *lower = p1->getPointPosition().y > p2->getPointPosition().y ? p2 : p1;

			for (auto i = lower->getTileIndex().y; i < higher->getTileIndex().y; i++)
			{
				size_t index = tiles[i][p1->getTileIndex().x]->getIndex();

				if (!(index == 0 ||
					(index >= 29 && index <= 34) ||
					(index >= 59 && index <= 63)))
					return false;
			}

		}
		else if (p1->getPointPosition().y == p2->getPointPosition().y)
		{
			Point *higher = p1->getPointPosition().x < p2->getPointPosition().x ? p2 : p1;
			Point *lower = p1->getPointPosition().x > p2->getPointPosition().x ? p2 : p1;

			for (auto i = lower->getTileIndex().x; i < higher->getTileIndex().x; i++)
			{
				size_t index = tiles[p1->getTileIndex().y][i]->getIndex();

				if (!(index == 0 ||
					(index >= 29 && index <= 34) ||
					(index >= 59 && index <= 63)))
				return false;
			}
		}

		return true;
	}
	return false;
}
