#include "GPS.hpp"
#include "../../States/Play/Game/mGame.hpp"

#include "../Minimap.hpp"
#include "../Radar.hpp"

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
	targetPos->resetPoint();
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
		else if (targetPos->getPointPosition() != playerPos->getPointPosition())
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

	std::vector<std::thread>threads;

	threads.push_back(std::thread(&GPS::checkAvailablePoints, this, std::ref(roadFromPlayer), targetPos, std::ref(roadLengthFromPlayer)));
	threads.push_back(std::thread(&GPS::checkAvailablePoints, this, std::ref(roadFromTarget), playerPos, std::ref(roadLengthFromTarget)));

	for (auto &i : threads)
		i.join();

	if (roadLengthFromPlayer < roadLengthFromTarget)
		bestRoad = roadFromPlayer;
	else
		bestRoad = roadFromTarget;

	optimazeRoad();
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

void GPS::optimazeRoad()
{
	for (size_t i = 0; i < bestRoad.size() - 2; ++i)
		if (checkRoadBeetwen(bestRoad[i], bestRoad[i + 2]))
			bestRoad.erase(bestRoad.begin() + i + 1, bestRoad.begin() + i + 2);
}

void GPS::createSegment(sf::RectangleShape &segment, Point * start, Point * stop)
{
	if (start->getPointPosition().x == stop->getPointPosition().x)
	{
		segment.setSize(sf::Vector2f(200 , start->getPointPosition().y - stop->getPointPosition().y));
		segment.setOrigin(100, 0);
		segment.setPosition(start->getPointPosition());
	}
	else // y is the same
	{
		segment.setSize(sf::Vector2f(start->getPointPosition().x - stop->getPointPosition().x, 200));
		segment.setOrigin(0, 100);
		segment.setPosition(start->getPointPosition());
	}

	segment.setRotation(180);
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
	sf::CircleShape point(100);
	point.setOrigin(point.getRadius(), point.getRadius());

	gpsTexture->clear();
	gpsTexture->draw(*radarTexture);

	for (size_t i = 0;i < bestRoad.size() - 1;++i)
	{
		sf::RectangleShape roadSegment;
		createSegment(roadSegment, bestRoad[i], bestRoad[i + 1]);
		
		// if it is mission - yellow color else violet

		roadSegment.setFillColor(sf::Color(164, 76, 242));
		point.setFillColor(sf::Color(164, 76, 242));

		point.setPosition(bestRoad[i]->getPointPosition());
		gpsTexture->draw(point);

		point.setPosition(bestRoad[i + 1]->getPointPosition());
		gpsTexture->draw(point);

		gpsTexture->draw(roadSegment);
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