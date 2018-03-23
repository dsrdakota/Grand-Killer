#include "MapInMenu.hpp"

#include "../../../../../../Map/Radar.hpp"
#include "../../../../../../Map/Minimap.hpp"

MapInMenu::MapInMenu()
{
	map = new sf::Sprite;
	mapArea = new sf::RectangleShape;

	cuttedMap = new sf::Sprite;
	cuttedMapTexture = new sf::RenderTexture;

	active = false;
}

MapInMenu::~MapInMenu()
{
	delete map;
	delete mapArea;
	delete cuttedMap;
}

void MapInMenu::setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	map->setTexture(*Radar::getRadarSprite()->getTexture());

	mapArea->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
	mapArea->setPosition(borderXrange.x, borderYrange.x);

	Minimap::Instance().scale = sf::Vector2f(0.25f, 0.25f);
	Minimap::Instance().setTilesScale();
	Minimap::Instance().centerMapOnPlayer();

	map->setScale(Minimap::Instance().scale);
	map->setPosition(TilesManager::getTilesVector()[0][0]->getTileMiniMapSprite()->getPosition());
	cutMap();

	player = Minimap::Instance().player;
	target = Minimap::Instance().target;
}

bool MapInMenu::exit()
{
	return !active;
}

void MapInMenu::drawActive()
{
	Minimap::Instance().show(true);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		active = false;

		player = Minimap::Instance().player;
		target = Minimap::Instance().target;

		map->setScale(Minimap::Instance().scale);
		map->setPosition(TilesManager::getTilesVector()[0][0]->getTileMiniMapSprite()->getPosition());
		cutMap();
	}
}

void MapInMenu::drawUnactive()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)))
	{
		active = true;
		Minimap::Instance().scale = sf::Vector2f(0.4f, 0.4f);
		Minimap::Instance().setTilesScale();
		Minimap::Instance().centerMapOnPlayer();
		Minimap::Instance().canSetTarget = false;
	}

	Painter::Instance().addToInterfaceDraw(cuttedMap);

	if (mapArea->getGlobalBounds().contains(player->getPosition()))
		Painter::Instance().addToInterfaceDraw(player);

	if (mapArea->getGlobalBounds().contains(target->getPosition()) && Minimap::Instance().targetIsSet)
		Painter::Instance().addToInterfaceDraw(target);
}

bool MapInMenu::isActive()
{
	return active;
}

bool MapInMenu::mouseOnMap()
{
	if (mapArea->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		return true;
	return false;
}

void MapInMenu::cutMap()
{
	map->setTexture(*Radar::getRadarSprite()->getTexture());

	cuttedMapTexture->create(static_cast<unsigned>(mapArea->getGlobalBounds().width), static_cast<unsigned>(mapArea->getGlobalBounds().height));

	cuttedMapTexture->clear(sf::Color(0,0,0,0));

	map->move(-mapArea->getPosition());
	cuttedMapTexture->draw(*map);

	cuttedMapTexture->display();

	cuttedMapTexture->setSmooth(true);

	cuttedMap->setTexture(cuttedMapTexture->getTexture());
	cuttedMap->setPosition(mapArea->getPosition());
}