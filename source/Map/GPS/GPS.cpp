#include "GPS.hpp"

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
		crossing.push_back(new Point(sf::Vector2u(
			tiles[point.y][point.x]->getTileSprite()->getPosition().x + TilesManager::getTileSize() / 2.f,
			tiles[point.y][point.x]->getTileSprite()->getPosition().y + TilesManager::getTileSize() / 2.f
		), point));

	for(const auto &i:crossing)
		setAllPointsToMoveable(i);

	radarTexture = new sf::Sprite(*Radar::Instance().getRadarSprite()->getTexture());

	gpsTexture = new sf::RenderTexture;
	gpsTexture->create(static_cast<unsigned>(Map::getMapSize().x), static_cast<unsigned>(Map::getMapSize().y));
}

void GPS::draw()
{
	Painter::Instance().addToDraw(crossing[1]->getTag());

	auto vector = crossing[1]->getPointsToMoveable();

	for (const auto &i : vector)
		Painter::Instance().addToDraw(i->getTag());
}

void GPS::findBestRoute()
{
	if (Minimap::Instance().isTargetSet())
	{
		getTheClosestAsphaltTileFromTarget(Minimap::Instance().targetTile->getTileSprite()->getPosition());
		//getTheClosestAsphaltTileFromTarget(Minimap::Instance().playerTile->getTileSprite()->getPosition());
	}
}

void GPS::setAllPointsToMoveable(Point * point)
{
	for (const auto &i : crossing)
		if (checkRoadBeetwen(point, i))
			point->addPointToMoveable(i);
}

void GPS::getTheClosestAsphaltTileFromTarget(const sf::Vector2f & position)
{
	sf::RectangleShape shape(sf::Vector2f(80, 80));
	shape.setFillColor(sf::Color::Red);

	shape.setOrigin(40, 40);

	float smallestLength = -1.f;

	for (const auto &i : crossing)
	{
		sf::Vector2f vector = position - i->getTag()->getPosition();
		float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);

		if (lenght < smallestLength ||
			smallestLength == -1.f)
		{
			smallestLength = lenght;

			shape.setPosition(i->getTag()->getPosition());
		}
	}

	gpsTexture->clear();
	
	gpsTexture->draw(*radarTexture);

	gpsTexture->draw(shape);

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