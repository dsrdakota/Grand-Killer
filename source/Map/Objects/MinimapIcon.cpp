#include "MinimapIcon.hpp"

#include "../../Engine/Engine.hpp"

#include <iostream>

MinimapIcon::MinimapIcon(const MinimapIconType & type, const sf::Vector2f & position, const float & angle)
{
	this->type = type;
	icon = new sf::Sprite(*TextureManager::get(typeToString(type)));
	icon->setOrigin(icon->getGlobalBounds().left + icon->getGlobalBounds().width / 2.f, icon->getGlobalBounds().top + icon->getGlobalBounds().height / 2.f);
	setPosition(position);
	updatePosition();
	icon->setRotation(angle);

	visibleCooldown = 2;

	drawable = true;
	blink = false;
	alwaysVisible = false;
}

MinimapIcon::~MinimapIcon()
{
	delete icon;
}

const MinimapIconType & MinimapIcon::getType()
{
	return type;
}

sf::Sprite * MinimapIcon::getSprite()
{
	return icon;
}

const sf::Vector2f & MinimapIcon::getPosition()
{
	return icon->getPosition();
}

Tile * MinimapIcon::getTile()
{
	return tile;
}

const sf::Vector2f & MinimapIcon::getLengthFromTile()
{
	return lengthFromTile;
}

void MinimapIcon::setPosition(const sf::Vector2f & position)
{
	tile = getTileUnderPosition(position);

	lengthFromTile = position- tile->getTileMapSprite()->getPosition();
	updatePosition();
}

void MinimapIcon::setPosition(Tile * tile, const sf::Vector2f & lengthFromTile)
{
	this->tile = tile;
	this->lengthFromTile = lengthFromTile;
}

void MinimapIcon::setRotation(const float & angle)
{
	icon->setRotation(angle);
}

void MinimapIcon::updatePosition(const sf::Vector2f& scale)
{
	icon->setPosition(sf::Vector2f(tile->getTileMiniMapSprite()->getPosition().x + lengthFromTile.x * scale.x,
		tile->getTileMiniMapSprite()->getPosition().y + lengthFromTile.y * scale.y));
}

void MinimapIcon::draw()
{
	if (blink)
		doBlink();
	else
		visibleCooldown = 2;

	if (drawable && visibleCooldown > 0)
		Painter::Instance().addToInterfaceDraw(icon);
}

void MinimapIcon::doBlink()
{
	if (time.time->asSeconds() >= 0.25f)
	{
		time.clock->restart();
		*time.time = sf::Time::Zero;

		if (visibleCooldown <= 0)
			visibleCooldown = 2;
		else
			visibleCooldown--;
	}
}

Tile * MinimapIcon::getTileUnderPosition(const sf::Vector2f & position)
{
	auto tileLeftUpCornerOfMap = TilesManager::getTilesVector()[0][0];

	size_t y = static_cast<size_t>((position.y - tileLeftUpCornerOfMap->getTileMiniMapSprite()->getPosition().y) / tileLeftUpCornerOfMap->getTileMiniMapSprite()->getGlobalBounds().height);

	if (y > static_cast<size_t>(TilesManager::getCountTile().y) - 1)
		y = static_cast<size_t>(TilesManager::getCountTile().y) - 1;
	else if (y < 0)
		y = 0;

	size_t x = static_cast<size_t>((position.x - tileLeftUpCornerOfMap->getTileMiniMapSprite()->getPosition().x) / tileLeftUpCornerOfMap->getTileMiniMapSprite()->getGlobalBounds().width);

	if (x > static_cast<size_t>(TilesManager::getCountTile().x) - 1)
		x = static_cast<size_t>(TilesManager::getCountTile().x) - 1;
	else if (x < 0)
		x = 0;

	return TilesManager::getTilesVector()[y][x];
}

std::string MinimapIcon::typeToString(const MinimapIconType & type)
{
	std::vector<std::string> stringTypes =
	{
		"playerMinimap",
		"targetMinimap",
		"missionTargetMinimap",
	};

	return stringTypes[(int)type];
}
