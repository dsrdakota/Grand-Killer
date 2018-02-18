#include "Radar.hpp"

#include "../../../../../Game.hpp"
#include "../../../../../Manager/renderSprites.hpp"

#include <iostream>

Radar::Radar() : window(Game::Instance().getWindow())
{
	radarArea = new sf::RectangleShape(sf::Vector2f(300, 150));
	radarArea->setFillColor(sf::Color(255, 0, 0, 100));

	radarTiles = Map::getTilesVector();

	scale = sf::Vector2f(0.1f, 0.1f);
	
	for (size_t i = 0;i < Map::getCountTile().y;++i)
		for (size_t j = 0;j < Map::getCountTile().x;++j)
		{
			auto tile = radarTiles[i][j]->getTileRadarSprite();
			tile->setScale(scale);
			tile->setPosition(radarArea->getPosition().x + j * (Map::getTileSize() * scale.x), radarArea->getPosition().y + i * (Map::getTileSize() * scale.y));
		}
}

Radar::~Radar()
{
	delete radarArea;
	delete player;
	delete target;
}

void Radar::update()
{
	radarArea->setPosition(sf::Vector2f(Map::getUpLeftCornerPosOfCurrentView().x + 40,
		Map::getUpLeftCornerPosOfCurrentView().y + window->getSize().y - radarArea->getSize().y - 80));
}

void Radar::setPlayerPosition(Tile * playerTile, const sf::Vector2f & lengthPlayerFromTileOrigin, const float & rot)
{
	this->playerTile = playerTile;
	this->lengthPlayerFromTileOrigin = lengthPlayerFromTileOrigin;
	playerRotation = rot;

	centerMapOnPlayer();
}

void Radar::centerMapOnPlayer()
{
	sf::Vector2f moveOffset = sf::Vector2f(radarArea->getGlobalBounds().width / 2.f  - (playerTile->getTileRadarSprite()->getPosition().x - radarArea->getPosition().x + lengthPlayerFromTileOrigin.x * scale.x),
		radarArea->getGlobalBounds().height / 2.f - (playerTile->getTileRadarSprite()->getPosition().y - radarArea->getPosition().y + lengthPlayerFromTileOrigin.y * scale.y));

	moveAllTiles(moveOffset);
}

void Radar::moveAllTiles(const sf::Vector2f & offset)
{
	for (const auto &i : radarTiles)
	{
		for (const auto &j : i)
		{
			j->getTileRadarSprite()->move(offset);

			if (radarArea->getPosition().y > j->getTileRadarSprite()->getPosition().y)
			{
				for (const auto &j : i)
					j->getTileRadarSprite()->setColor(sf::Color(255, 255, 255, 0));
			}
			else
			{
				for (const auto &j : i)
					j->getTileRadarSprite()->setColor(sf::Color(255, 255, 255, 255));
			}
		}
	}
}

void Radar::draw()
{
	//renderSprites::Instance().addToRender(radarArea);

	for (const auto &i : radarTiles)
		for (const auto &j : i)
			if (radarArea->getGlobalBounds().intersects(j->getTileRadarSprite()->getGlobalBounds()))
				renderSprites::Instance().addToRender(j->getTileRadarSprite());
}
