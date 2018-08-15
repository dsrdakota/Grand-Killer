#include "GPS.hpp"
#include "../../States/Play/Game/mGame.hpp"

#include "../Minimap.hpp"
#include "../Radar.hpp"

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
}

void GPS::setPlayer(IObject * player)
{
	this->player = player;
}

void GPS::setTarget()
{
	targetPos->resetPoint();
	targetPos->setPosition(getTheClosestAsphaltPosFromTarget(Minimap::Instance().targetTile->getTileMapSprite()->getPosition()));

	for (const auto &i : crossing)
		if (checkRoadBeetwen(targetPos, i))
			targetPos->addPointToMoveable(i);
}

void GPS::setMission()
{
	missionPos->resetPoint();
	missionPos->setPosition(getTheClosestAsphaltPosFromTarget(Minimap::Instance().targetTile->getTileMapSprite()->getPosition()));

	for (const auto &i : crossing)
		if (checkRoadBeetwen(missionPos, i))
			missionPos->addPointToMoveable(i);
}

void GPS::findBestRoute()
{
	if (Minimap::Instance().isTargetSet() && Minimap::Instance().map->getGlobalBounds().contains(Minimap::Instance().target->getPosition())
		/* || is mission*/)
	{
		clear();

		playerPos->setPosition(getTheClosestAsphaltPosFromTarget(player->getPosition()));

		if (targetPos->getPointPosition() == playerPos->getPointPosition() &&
			mGame::Instance().getGameState() == mGame::state::MainGame)
			Minimap::Instance().targetIsSet = false;

		else if (targetPos->getPointPosition() != playerPos->getPointPosition())
		{
			playerPos->resetPoint();

			for (const auto &i : crossing)
				if (checkRoadBeetwen(playerPos, i))
					playerPos->addPointToMoveable(i);

			doRoad();
			drawGpsTexture(sf::Color(164, 76, 242));
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

std::vector<sf::RectangleShape*>& GPS::getDirections()
{
	return directions;
}

std::vector<sf::CircleShape*>& GPS::getLinks()
{
	return links;
}

void GPS::doRoad()
{
	bestRoad.clear();
	
	std::vector<Point*> roadFromPlayer;
	std::vector<Point*> roadFromTarget;

	float roadLengthFromPlayer = -1;
	float roadLengthFromTarget = -1;

	roadFromPlayer.push_back(playerPos);
	roadFromTarget.push_back(targetPos);

	if (checkRoadBeetwen(playerPos, targetPos))
	{
		bestRoad.push_back(playerPos);
		bestRoad.push_back(targetPos);
		return;
	}

	checkAvailablePoints(roadFromPlayer, targetPos, roadLengthFromPlayer);
	checkAvailablePoints(roadFromTarget, playerPos, roadLengthFromTarget);

	if (roadLengthFromPlayer < roadLengthFromTarget)
		bestRoad = roadFromPlayer;
	else
		bestRoad = roadFromTarget;
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
// if it is mission - yellow color else violet
void GPS::drawGpsTexture(const sf::Color &roadColor)
{
	auto createLink = [&](const sf::Vector2f &position) {
		sf::CircleShape *point = new sf::CircleShape(100);
		point->setOrigin(point->getRadius(), point->getRadius());
		point->setFillColor(roadColor);
		point->setPosition(position);
		links.push_back(point);
	};

	createLink(targetPos->getPointPosition());

	for (size_t i = 0;i < bestRoad.size() - 1;++i)
	{
		sf::RectangleShape *roadSegment = createSegment(bestRoad[i], bestRoad[i + 1]);
	
		for (size_t j = 0;j < 2;++j)
			createLink(bestRoad[i]->getPointPosition());

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
