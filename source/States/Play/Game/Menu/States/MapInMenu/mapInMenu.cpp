#include "MapInMenu.hpp"

#include "../../../../../../Map/Radar.hpp"
#include "../../../../../../Map/Minimap.hpp"
#include "../../../../../../Map/GPS/GPS.hpp"
#include "../../../../../../Map/ObjectsManager/MinimapIcons.hpp"


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
	map->setPosition(map->getPosition() - mapArea->getPosition());

	player = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Player]->getSprite();
	target = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Target]->getSprite();
	missionTarget = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::MissionTarget]->getSprite();
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

		player = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Player]->getSprite();
		target = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Target]->getSprite();
		missionTarget = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::MissionTarget]->getSprite();

		map->setScale(Minimap::Instance().scale);
		map->setPosition(TilesManager::getTilesVector()[0][0]->getTileMiniMapSprite()->getPosition());
		map->setPosition(map->getPosition() - mapArea->getPosition());
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
	Minimap::Instance().setGPSOnMinimap();
	cutMap();
	Painter::Instance().addToInterfaceDraw(cuttedMap);

	if (mapArea->getGlobalBounds().contains(player->getPosition()))
		Painter::Instance().addToInterfaceDraw(player);

	if (mapArea->getGlobalBounds().contains(target->getPosition()) && Minimap::Instance().targetIsSet)
		Painter::Instance().addToInterfaceDraw(target);

	if (mapArea->getGlobalBounds().contains(missionTarget->getPosition()) && Minimap::Instance().missionTargetIsSet)
		Painter::Instance().addToInterfaceDraw(missionTarget);
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
	cuttedMapTexture->create(static_cast<unsigned>(mapArea->getGlobalBounds().width), static_cast<unsigned>(mapArea->getGlobalBounds().height));

	cuttedMapTexture->clear(sf::Color(0, 0, 0, 0));

	cuttedMapTexture->draw(*map);

	if (Minimap::Instance().targetIsSet || Minimap::Instance().missionTargetIsSet)
	{
		for (const auto &i : GPS::Instance().getLinks())
		{
			sf::Vector2f pos = i->getPosition();
			i->setPosition(i->getPosition() - mapArea->getPosition());
			cuttedMapTexture->draw(*i);

			i->setPosition(pos);
		}

		for (const auto &i : GPS::Instance().getDirections())
		{
			sf::Vector2f pos = i->getPosition();
			i->setPosition(i->getPosition() - mapArea->getPosition());
			cuttedMapTexture->draw(*i);

			i->setPosition(pos);
		}
	}

	cuttedMapTexture->display();

	cuttedMapTexture->setSmooth(true);
	
	cuttedMap->setTexture(cuttedMapTexture->getTexture());
	cuttedMap->setPosition(mapArea->getPosition());
}