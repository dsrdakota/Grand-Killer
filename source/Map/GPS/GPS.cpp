#include "GPS.hpp"
#include "../../States/Play/Game/mGame.hpp"

#include "../Minimap.hpp"
#include "../Radar.hpp"

#include <iostream>
#include <fstream>

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

	for(const auto &i:crossing)
		checkMoveablePoints(i);

	std::vector<Point*>linkedPoints;
	
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

	playerPos = new Point(sf::Vector2f(0, 0));
	targetPos = new Point(sf::Vector2f(0, 0));

	radarTexture = new sf::Sprite(*Radar::Instance().getRadarSprite()->getTexture());

	gpsTexture = new sf::RenderTexture;
	gpsTexture->create(static_cast<unsigned>(Map::getMapSize().x), static_cast<unsigned>(Map::getMapSize().y));
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
	targetPos->setPosition(getTheClosestAsphaltPosFromTarget(Minimap::Instance().targetTile->getTileMapSprite()->getPosition()));
	
	for (const auto &i : crossing)
		if (checkRoadBeetwen(targetPos, i))
			targetPos->addPointToMoveable(i);
}

void GPS::findBestRoute()
{
	if (Minimap::Instance().isTargetSet() && Minimap::Instance().map->getGlobalBounds().contains(Minimap::Instance().target->getPosition()))
	{
		playerPos->setPosition(getTheClosestAsphaltPosFromTarget(player->getPosition()));

		if (targetPos->getPointPosition() == playerPos->getPointPosition() &&
			mGame::Instance().getGameState() == mGame::state::MainGame)
		{
			Minimap::Instance().targetIsSet = false;
			Radar::Instance().resetTexture();
		}
		else if(targetPos->getPointPosition() != playerPos->getPointPosition())
		{
			playerPos->resetPoint();

			for (const auto &i : crossing)
				if (checkRoadBeetwen(playerPos, i))
					playerPos->addPointToMoveable(i);

			doRoad();
			drawGpsTexture();
		}
	}
}

void GPS::doRoad()
{
	std::vector<std::thread>threads;

	isRoadFinded = false;
	bestRoad.clear();

	actualRoadLength = -1;

	std::vector<Point*>road;
	road.push_back(playerPos);

	if (checkRoadBeetwen(playerPos, targetPos))
	{
		road.push_back(targetPos);
		bestRoad = road;
		return;
	}

	while(std::find(bestRoad.begin(), bestRoad.end(), targetPos) == bestRoad.end())
		checkAvailablePoints(road);
}

void GPS::checkAvailablePoints(std::vector<Point*> &actualRoad)
{
	Point* point = nullptr;
	float smallestLength = -1.f;

	for (const auto &i : actualRoad[actualRoad.size() - 1]->getPointsToMoveable())
	{
		if (std::find(actualRoad.begin(), actualRoad.end(), i) != actualRoad.end())
			continue;

		if (checkRoadBeetwen(targetPos, i))
		{
			actualRoad.push_back(i);
			actualRoad.push_back(targetPos);

			float length = 0;
			for (size_t i = 0; i < actualRoad.size() - 1; ++i)
			{
				sf::Vector2f len = actualRoad[i]->getPointPosition() - actualRoad[i + 1]->getPointPosition();
				length += sqrt(len.x * len.x + len.y *len.y);
			}

			if (actualRoadLength == -1 ||
				actualRoadLength > length)
			{
				actualRoadLength = length;
				bestRoad = actualRoad;
			}

			actualRoad.pop_back();
			actualRoad.pop_back();

			continue;
		}

		sf::Vector2f vector = targetPos->getPointPosition() - i->getPointPosition();
		float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);

		if (lenght < smallestLength ||
			smallestLength == -1.f)
		{
			smallestLength = lenght;
			point = i;
		}
	}

	if (std::find(actualRoad.begin(), actualRoad.end(), targetPos) == actualRoad.end() && point)
		actualRoad.push_back(point);
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

	for (const auto &i : linkCrossing)
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

void GPS::drawGpsTexture()
{
	sf::RectangleShape shape(sf::Vector2f(80, 80));
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(40, 40);

	gpsTexture->clear();
	gpsTexture->draw(*radarTexture);

	shape.setPosition(playerPos->getPointPosition());
	gpsTexture->draw(shape);

	for (const auto &i : bestRoad)
	{
		shape.setPosition(i->getPointPosition());
		gpsTexture->draw(shape);
	}

	gpsTexture->display();
	gpsTexture->setSmooth(true);

	Radar::Instance().getRadarSprite()->setTexture(gpsTexture->getTexture());
	Minimap::Instance().map->setTexture(gpsTexture->getTexture());
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
				if (tiles[i][p1->getTileIndex().x]->getIndex() >= 64)
					return false;

		}
		else if (p1->getPointPosition().y == p2->getPointPosition().y)
		{
			Point *higher = p1->getPointPosition().x < p2->getPointPosition().x ? p2 : p1;
			Point *lower = p1->getPointPosition().x > p2->getPointPosition().x ? p2 : p1;

			for (auto i = lower->getTileIndex().x; i < higher->getTileIndex().x; i++)
				if (tiles[p1->getTileIndex().y][i]->getIndex() >= 64)
					return false;
		}

		return true;
	}
	return false;
}