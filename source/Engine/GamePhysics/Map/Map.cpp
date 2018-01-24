#include "Map.hpp"

#include "../../../Manager/Texture.hpp"
#include "../../../Manager/renderSprites.hpp"
#include "../../../Game.hpp"

#include <fstream>

Map::Map() : window(Game::Instance().getWindow())
{
	tilesManager::Instance();

	view = new sf::View(sf::Vector2f(100,100), sf::Vector2f(window->getSize()));

	TileSize = new const short int(80);
	tilesCountWidth = new const short int(75);
	tilesCountHeigth = new const short int(75);

	mapSize = new sf::Vector2f(*TileSize * *tilesCountWidth, *TileSize * *tilesCountHeigth);

	std::ifstream file("data/Map/Tileset/Tiles.txt"); // binary soon

	for (int i = 0; i<*tilesCountHeigth; i++)
	{
		std::vector<Tile*>buf;
		for (int j = 0; j<*tilesCountWidth; j++)
		{
			int a;
			file >> a;
			buf.push_back(new Tile(a, sf::Vector2f(static_cast<float>(j * *TileSize),static_cast<float>(i * *TileSize))));
		}
		Tiles.push_back(buf);
	}

	file.clear();
	file.close();

	otherElements = new Other;
	trafficSigns = new TrafficSigns;
	trafficLights = new TrafficLights;
}

Map::~Map()
{
	window->setView(window->getDefaultView());

	delete TileSize;
	delete tilesCountHeigth;
	delete tilesCountWidth;

	for (const auto &i : Tiles)
		for (const auto &j : i)
			delete j;

	delete otherElements;
	delete trafficSigns;
	delete trafficLights;
}

void Map::setView(const sf::Vector2f & center)
{
	view->setCenter(center);
	window->setView(*view);
}

void Map::setRotation(const float & angle)
{
	//view->setRotation(angle);
}

void Map::updateView(const sf::Vector2f &newerView)
{
	setView(newerView);

	if (view->getCenter().x - view->getSize().x / 2 < 0)
		setView(sf::Vector2f(view->getSize().x / 2, view->getCenter().y));

	else if (view->getCenter().x + view->getSize().x / 2 > mapSize->x)
		setView(sf::Vector2f(mapSize->x - view->getSize().x / 2, view->getCenter().y));

	if (view->getCenter().y - view->getSize().y / 2 < 0)
		setView(sf::Vector2f(view->getCenter().x, view->getSize().y / 2));

	else if (view->getCenter().y + view->getSize().y / 2 > mapSize->y)
		setView(sf::Vector2f(view->getCenter().x, mapSize->y - view->getSize().y / 2));
	
}

void Map::drawUnder()
{
	for (const auto &i : Tiles)
		for (const auto &j : i)
		{
			const auto &sprite = j->getTileSprite();
			if (!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)) ||
				!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)))
				j->draw();
		}

	//trafficSigns->drawUnder();

	//trafficLights->drawUnder();
}

void Map::drawOn()
{
	//otherElements->draw();

	//trafficSigns->drawOn();

	//trafficLights->drawOn();
}

bool Map::isOutsideView(const sf::Vector2f & pos)
{
	const sf::Vector2f viewSize = Map::Instance().view->getSize();
	const sf::Vector2f viewPos = Map::Instance().view->getCenter();

	if (pos.x > viewPos.x - viewSize.x / 2 - 10 &&
		pos.x < viewPos.x + viewSize.x / 2 + 10 &&
		pos.y > viewPos.y - viewSize.y / 2  - 10 &&
		pos.y < viewPos.y + viewSize.y / 2 + 10)

		return false;

	return true;
}

bool Map::isPointOnGrass(const sf::Vector2f & pos)
{
	auto allTileWithGrass = tilesManager::Instance().getOnlyGrassTiles();

	for (auto &i : allTileWithGrass)
	{
		if (i->getTileSprite()->getGlobalBounds().contains(pos))
		{
			// sprawdzenie hitboxa

			return true;
		}
	}	

	return false;
}

bool Map::isPointInCollisionArea(const sf::Vector2f & pos)
{
	auto &map = Instance();
	if (pos.x < 0 || pos.x > map.mapSize->x)
		return true;
	if (pos.y < 0 || pos.y > map.mapSize->y)
		return true;

	// other
	
	return false;
}

sf::Vector2f Map::getUpLeftCornerPosOfCurrentView()
{
	auto &map = Instance();
	return sf::Vector2f(map.view->getCenter().x - map.view->getSize().x / 2,
		map.view->getCenter().y - map.view->getSize().y / 2);
}
