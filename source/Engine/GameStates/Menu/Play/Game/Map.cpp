#include "Map.hpp"

#include "../../../../../Manager/Texture.hpp"
#include "../../../../../Manager/renderSprites.hpp"
#include "../../../../../Game.hpp"

#include <iostream>

Map::Map() : window(Game::Instance().getWindow())
{
	map = new sf::Sprite(*textureManager::load("background", "data/Map/map.png"));
	view = new sf::View(sf::Vector2f(100,100), sf::Vector2f(1366,768));

	grassHitbox = new sf::Image;
	grassHitbox->loadFromFile("data/Map/Hitboxes/grassHitbox.png");
	collisionHitbox = new sf::Image;
	collisionHitbox->loadFromFile("data/Map/Hitboxes/collisionHitbox.png");

	swimmingPool = new SwimmingPool;
	otherElements = new Other;
	trafficSigns = new TrafficSigns;
}

Map::~Map()
{
	window->setView(window->getDefaultView());
	delete map;

	delete grassHitbox;
	delete collisionHitbox;
	delete swimmingPool;
	delete otherElements;
}

void Map::setView(const sf::Vector2f & center)
{
	view->setCenter(center);
	window->setView(*view);
}

void Map::updateView(const sf::Vector2f &newerView)
{
	setView(newerView);

	if (view->getCenter().x - view->getSize().x / 2 < 0)
		setView(sf::Vector2f(view->getSize().x / 2, view->getCenter().y));

	if (view->getCenter().y - view->getSize().y / 2 < 0)
		setView(sf::Vector2f(view->getCenter().x, view->getSize().y / 2));

	if (view->getCenter().x + view->getSize().x / 2 > map->getTexture()->getSize().x)
		setView(sf::Vector2f(map->getTexture()->getSize().x - view->getSize().x / 2, view->getCenter().y));

	if (view->getCenter().y + view->getSize().y / 2 > map->getTexture()->getSize().y)
		setView(sf::Vector2f(view->getCenter().x, map->getTexture()->getSize().y - view->getSize().y / 2));
	
}

void Map::drawUnder()
{
	renderSprites::Instance().addToRender(map);

	swimmingPool->draw();

	trafficSigns->drawUnder();
}

void Map::drawOn()
{
	otherElements->draw();

	trafficSigns->drawOn();
}

bool Map::isOutsideView(const sf::Vector2f & pos)
{
	const sf::Vector2f viewSize = Map::Instance().view->getSize();
	const sf::Vector2f viewPos = Map::Instance().view->getCenter();

	if (pos.x > viewPos.x - viewSize.x / 2 &&
		pos.x < viewPos.x + viewSize.x / 2 &&
		pos.y > viewPos.y - viewSize.y / 2 &&
		pos.y < viewPos.y + viewSize.y / 2)

		return false;

	return true;
}