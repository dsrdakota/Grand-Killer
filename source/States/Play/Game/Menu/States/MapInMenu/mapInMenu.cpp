#include "MapInMenu.hpp"

#include "../../../../../../Map/Radar.hpp"

#include <iostream>

MapInMenu::MapInMenu()
{
	mapTiles = TilesManager::getTilesVector();

	map = new sf::Sprite;
	mapArea = new sf::RectangleShape;

	scale = sf::Vector2f(0, 0);

	player = new sf::Sprite(*TextureManager::get("playerMinimap"));
	player->setOrigin(player->getGlobalBounds().left + player->getGlobalBounds().width / 2.f, player->getGlobalBounds().top + player->getGlobalBounds().height / 2.f);

	target = new sf::Sprite(*TextureManager::get("targetMinimap"));
	target->setOrigin(target->getGlobalBounds().left + target->getGlobalBounds().width / 2.f, target->getGlobalBounds().top + target->getGlobalBounds().height / 2.f);

	active = false;
}

MapInMenu::~MapInMenu()
{
	delete map;
	delete mapArea;
	delete player;

	delete target;

	for (const auto &i : navigation)
	{
		delete i.first;
		delete i.second;
	}
}

void MapInMenu::setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	this->menuPos = menuPos;

	map->setTexture(*Radar::getRadarSprite()->getTexture());

	mapArea->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
	mapArea->setPosition(borderXrange.x, borderYrange.x);

	scale = sf::Vector2f(mapArea->getSize().x / (TilesManager::getCountTile().x * TilesManager::getTileSize()),
		mapArea->getSize().y / (TilesManager::getCountTile().y * TilesManager::getTileSize()));
	setTilesScale();
	cutTiles();
}

bool MapInMenu::exit()
{
	return !active;
}

void MapInMenu::drawActive()
{
	//Minimap::show();

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		active = false;
}

void MapInMenu::drawUnactive()
{
	//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)))
		//active = true;

	for (size_t i = 0;i<TilesManager::getCountTile().y;++i)
		for (size_t j = 0;j<TilesManager::getCountTile().x;++j)
			if (mapArea->getGlobalBounds().intersects(mapTiles[i][j]->getTileMapSprite()->getGlobalBounds()))
				Painter::Instance().addToDraw(mapTiles[i][j]->getTileMapSprite());
	draw();
}

void MapInMenu::setPlayerPosition(Tile *playerTile, const sf::Vector2f &lengthPlayerFromTileOrigin, const float &rot)
{
	this->playerTile = playerTile;
	this->lengthPlayerFromTileOrigin = lengthPlayerFromTileOrigin;
	playerRotation = rot;
}

bool MapInMenu::isActive()
{
	return active;
}

bool MapInMenu::mouseOnMap()
{
	if (mapArea->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
		return true;
	return false;
}

void MapInMenu::updateIcons()
{
	map->setPosition(mapTiles[0][0]->getTileMapSprite()->getPosition());

	player->setPosition(sf::Vector2f(playerTile->getTileMapSprite()->getPosition().x + lengthPlayerFromTileOrigin.x * scale.x,
		playerTile->getTileMapSprite()->getPosition().y + lengthPlayerFromTileOrigin.y * scale.y));
	player->setRotation(playerRotation);

	//if (targetIsSet)
		//setTarget();
}

void MapInMenu::setTilesScale()
{
	for (size_t i = 0;i < TilesManager::getCountTile().y;++i)
		for (size_t j = 0;j < TilesManager::getCountTile().x;++j)
		{
			auto tile = mapTiles[i][j]->getTileMapSprite();
			tile->setScale(scale);
			tile->setPosition(mapArea->getPosition().x + j * (TilesManager::getTileSize() * scale.x), mapArea->getPosition().y + i * (TilesManager::getTileSize() * scale.y));
		}

	map->setScale(scale);
	updateIcons();
}

void MapInMenu::cutTiles()
{
	for (size_t i = 0;i < TilesManager::getCountTile().y;++i)
		for (size_t j = 0;j < TilesManager::getCountTile().x;++j)
		{
			auto tile = mapTiles[i][j]->getTileMapSprite();

			// reset
			tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(TilesManager::getTileSize(), TilesManager::getTileSize())));

			if (!active && mapArea->getGlobalBounds().intersects(tile->getGlobalBounds()))
			{
				if (mapArea->getGlobalBounds().contains(tile->getPosition()) &&
					mapArea->getGlobalBounds().contains(tile->getPosition().x + tile->getGlobalBounds().width, tile->getPosition().y) &&
					mapArea->getGlobalBounds().contains(tile->getPosition().x + tile->getGlobalBounds().width, tile->getPosition().y + tile->getGlobalBounds().height) &&
					mapArea->getGlobalBounds().contains(tile->getPosition().x, tile->getPosition().y + tile->getGlobalBounds().height))

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(TilesManager::getTileSize(), TilesManager::getTileSize())));


				// upper border

				if (mapArea->getPosition().y > tile->getPosition().y &&
					mapArea->getPosition().y < tile->getPosition().y + tile->getGlobalBounds().height)
				{
					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, static_cast<int>(mapArea->getPosition().y - tile->getPosition().y)),
						sf::Vector2i(TilesManager::getTileSize(), static_cast<int>(TilesManager::getTileSize() - (mapArea->getPosition().y - tile->getPosition().y)))));
					tile->move(0, mapArea->getPosition().y - tile->getPosition().y);
				}

				// bottom border

				else if (mapArea->getPosition().y + mapArea->getGlobalBounds().height > tile->getPosition().y &&
					mapArea->getPosition().y + mapArea->getPosition().y + mapArea->getGlobalBounds().height < tile->getPosition().y + tile->getGlobalBounds().height)

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
						sf::Vector2i(TilesManager::getTileSize(), static_cast<int>(TilesManager::getTileSize() - ((tile->getPosition().y + tile->getGlobalBounds().height) - (mapArea->getPosition().y + mapArea->getGlobalBounds().height))))));

				// left border

				if (mapArea->getPosition().x > tile->getPosition().x &&
					mapArea->getPosition().x < tile->getPosition().x + tile->getGlobalBounds().width)
				{
					tile->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>(mapArea->getPosition().x - tile->getPosition().x), 0),
						sf::Vector2i(static_cast<int>(TilesManager::getTileSize() - (mapArea->getPosition().x - tile->getPosition().x)), TilesManager::getTileSize())));
					tile->move(mapArea->getPosition().x - tile->getPosition().x, 0);
				}

				// right border

				else if (mapArea->getPosition().x + mapArea->getGlobalBounds().width > tile->getPosition().x &&
					mapArea->getPosition().x + mapArea->getGlobalBounds().width < tile->getPosition().x + tile->getGlobalBounds().width)

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
						sf::Vector2i(static_cast<int>(TilesManager::getTileSize() - ((tile->getPosition().x + tile->getGlobalBounds().width) - (mapArea->getPosition().x + mapArea->getGlobalBounds().width))), TilesManager::getTileSize())));
			}
		}
}

void MapInMenu::draw()
{
	if (mapArea->getGlobalBounds().contains(player->getPosition()))
		Painter::Instance().addToDraw(player);

	if (mapArea->getGlobalBounds().contains(target->getPosition()) /*&& targetIsSet*/)
		Painter::Instance().addToDraw(target);
}

void MapInMenu::setTarget()
{
	target->setPosition(sf::Vector2f(targetTile->getTileMapSprite()->getPosition().x + lengthTargetFromTileOrigin.x,
		targetTile->getTileMapSprite()->getPosition().y + lengthTargetFromTileOrigin.y));
}