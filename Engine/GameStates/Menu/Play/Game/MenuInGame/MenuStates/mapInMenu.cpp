#include "mapInMenu.hpp"

#include "../../../../../../../Manager/Texture.hpp"
#include "../../../../../../../Manager/renderSprites.hpp"

#include <iostream>

mapInMenu::mapInMenu()
{
	textureManager::load("mapInMenu", "data/Map/Minimap/minimap.png");
	map = new sf::RectangleShape;
	player = new sf::CircleShape(5);
	player->setFillColor(sf::Color::Green);
	player->setOrigin(5, 5);
	active = false;
	mapRect = sf::IntRect(0, 0, window->getSize().x, window->getSize().x);
}

mapInMenu::~mapInMenu()
{
	delete map;
	delete player;
}

void mapInMenu::setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	if (!active)
	{
		map->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
		map->setPosition(borderXrange.x, borderYrange.x);
	}
	else
	{
		map->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x + 50));
		map->setPosition(borderXrange.x, borderYrange.x - 50);
	}

	map->setTexture(dynamic_cast<const sf::Texture*>(textureManager::get("mapInMenu")));
}

bool mapInMenu::exit()
{
	return !active;
}

void mapInMenu::drawActive()
{
	toControl();

	draw();

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		map->setTexture(dynamic_cast<const sf::Texture*>(textureManager::get("mapInMenu")), true);
		mapRect = sf::IntRect(0, 0, window->getSize().x, window->getSize().y);
		active = false;
	}
}

void mapInMenu::drawUnactive()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)))
	{
		active = true;
		mapRect = sf::IntRect(static_cast<int>(playerPosition.x - map->getSize().x / 2.f), static_cast<int>(playerPosition.y - map->getSize().y / 2.f), window->getSize().x, window->getSize().y);
	}

	draw();
}

void mapInMenu::setPlayerPosition(const sf::Vector2f & pos)
{
	playerPosition = pos;
	player->setPosition(map->getPosition().x + (pos.x * (map->getSize().x * (6000.f / map->getTextureRect().width) / 6000.f)) - (mapRect.left * (map->getSize().x * (6000.f / map->getTextureRect().width) / 6000.f)),
		map->getPosition().y + (pos.y * (map->getSize().y * (6000.f / map->getTextureRect().height) / 6000.f)) - (mapRect.top * (map->getSize().y * (6000.f / map->getTextureRect().height) / 6000.f))); 
	// dont keep me change it
}

bool mapInMenu::isActive()
{
	return active;
}

void mapInMenu::toControl()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mapRect.top > 0)
		mapRect.top -= 10;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mapRect.top + mapRect.height< 6000)
		mapRect.top += 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mapRect.left > 0)
		mapRect.left -= 10;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mapRect.left + mapRect.width < 6000)
		mapRect.left += 10;

	if (Game::getScrollValue() > 0 && mapRect.width > static_cast<int>(window->getSize().x) && mapRect.height > static_cast<int>(window->getSize().y))
	{
		mapRect.height -= 10;
		mapRect.width -= 10;
		if (mapRect.top + mapRect.height < 6000)
			mapRect.top += 5;
		if(mapRect.left + mapRect.width < 6000)
			mapRect.left += 5;
	}
	else if(Game::getScrollValue() < 0 && mapRect.width < 6000 && mapRect.height < 6000)
	{
		mapRect.height += 10;
		mapRect.width += 10;

		if (mapRect.top + mapRect.height < 6000 && mapRect.top > 0)
			mapRect.top -= 5;
		else if (mapRect.top < 0)
			mapRect.top += 10;
		else
			mapRect.top -= 10;

		if (mapRect.left + mapRect.width < 6000 && mapRect.left > 0)
			mapRect.left -= 5;
		else if (mapRect.left < 0)
			mapRect.left += 10;
		else
			mapRect.left -= 10;
	}

	map->setTextureRect(mapRect);
}

bool mapInMenu::mouseOnMap()
{
	if (map->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
		return true;
	return false;
}

void mapInMenu::draw()
{
	renderSprites::Instance().addToRender(map);
	renderSprites::Instance().addToRender(player);
}
