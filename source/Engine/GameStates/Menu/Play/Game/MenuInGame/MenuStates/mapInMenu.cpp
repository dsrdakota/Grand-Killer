#include "mapInMenu.hpp"

#include "../../../../../../../Manager/Texture.hpp"
#include "../../../../../../../Manager/renderSprites.hpp"

#include <iostream>

mapInMenu::mapInMenu()
{
	mapTiles = Map::getTilesVector();

	map = new sf::RectangleShape;
	map->setFillColor(sf::Color(1, 36, 3, 220));

	scale = sf::Vector2f(0, 0);
	maxScale = new sf::Vector2f(0.6f, 0.6f);
	minScale = new sf::Vector2f(0.15f, 0.15f);

	mapSizeActive = static_cast<sf::Vector2f>(window->getSize());

	player = new sf::Sprite(*textureManager::load("playerMinimap", "data/Map/Minimap/player.png"));
	player->setOrigin(player->getGlobalBounds().left + player->getGlobalBounds().width / 2.f, player->getGlobalBounds().top + player->getGlobalBounds().height / 2.f);

	target = new sf::Sprite(*textureManager::load("targetMinimap", "data/Map/Minimap/target.png"));
	target->setOrigin(target->getGlobalBounds().left + target->getGlobalBounds().width / 2.f, target->getGlobalBounds().top + target->getGlobalBounds().height / 2.f);

	for (int i = 0;i < 4;++i)
	{
		sf::RectangleShape *buf = new sf::RectangleShape(sf::Vector2f(1, 10));
		buf->setFillColor(sf::Color::White);
		buf->setOutlineThickness(1);
		buf->setOutlineColor(sf::Color::Black);
		buf->setOrigin(0.5, 0);
		tag.push_back(buf);
	}

	tag[1]->setRotation(90);
	tag[2]->setRotation(180);
	tag[3]->setRotation(270);

	centerOfTag = new sf::CircleShape(3);
	centerOfTag->setOrigin(3, 3);

	targetIsSet = false;
	canSetTarget = false;

	playerIsVisible = 2;

	active = false;

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PUNKT TRASY"), Keyboard::Instance().getKeySprite(Keyboard::Keys::Enter)));
	navigation[0].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WROC"), Keyboard::Instance().getKeySprite(Keyboard::Keys::Esc)));
	navigation[1].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::D)));
	navigation[2].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::A)));
	navigation[3].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::S)));
	navigation[4].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PORUSZANIE KAMERA"), Keyboard::Instance().getKeySprite(Keyboard::Keys::W)));
	navigation[5].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), Keyboard::Instance().getKeySprite(Keyboard::Keys::PageDown)));
	navigation[6].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "ZOOM"), Keyboard::Instance().getKeySprite(Keyboard::Keys::PageUp)));
	navigation[7].second->setScale(0.9f, 0.9f);
}

mapInMenu::~mapInMenu()
{
	delete map;
	delete player;

	for (const auto &i : navigation)
	{
		delete i.first;
		delete i.second;
	}

	for (const auto &i : tag)
		delete i;

	delete centerOfTag;

	delete minScale;
	delete maxScale;
}

void mapInMenu::setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	this->menuPos = menuPos;

	map->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
	map->setPosition(borderXrange.x, borderYrange.x);

	mapSizeUnactive = map->getSize();
	mapPosUnactive = map->getPosition();

	navigation[0].second->setPosition(menuPos.x + window->getSize().x - navigation[0].second->getGlobalBounds().width - 40,
		menuPos.y + window->getSize().y - navigation[0].second->getGlobalBounds().height - 15);
	navigation[0].first->text->setPosition(navigation[0].second->getPosition().x - navigation[0].first->text->getGlobalBounds().width,
		navigation[0].second->getPosition().y + navigation[0].second->getGlobalBounds().height / 2 - navigation[0].first->text->getGlobalBounds().height);

	navigation[1].second->setPosition(navigation[0].first->text->getPosition().x - 40,
		navigation[0].second->getPosition().y);
	navigation[1].first->text->setPosition(navigation[1].second->getPosition().x - navigation[1].first->text->getGlobalBounds().width,
		navigation[1].second->getPosition().y + navigation[1].second->getGlobalBounds().height / 2 - navigation[1].first->text->getGlobalBounds().height);

	navigation[2].second->setPosition(navigation[1].first->text->getPosition().x - 40,
		navigation[1].second->getPosition().y);
	navigation[3].second->setPosition(navigation[2].second->getPosition().x - 33,
		navigation[2].second->getPosition().y);
	navigation[4].second->setPosition(navigation[3].second->getPosition().x - 33,
		navigation[3].second->getPosition().y);
	navigation[5].second->setPosition(navigation[4].second->getPosition().x - 33,
		navigation[4].second->getPosition().y);
	navigation[5].first->text->setPosition(navigation[5].second->getPosition().x - navigation[5].first->text->getGlobalBounds().width,
		navigation[5].second->getPosition().y + navigation[5].second->getGlobalBounds().height / 2 - navigation[5].first->text->getGlobalBounds().height);

	navigation[6].second->setPosition(navigation[5].first->text->getPosition().x - 40,
		navigation[5].second->getPosition().y);
	navigation[7].second->setPosition(navigation[6].second->getPosition().x - 33,
		navigation[6].second->getPosition().y);
	navigation[7].first->text->setPosition(navigation[7].second->getPosition().x - navigation[7].first->text->getGlobalBounds().width - 5,
		navigation[7].second->getPosition().y + navigation[7].second->getGlobalBounds().height / 2 - navigation[7].first->text->getGlobalBounds().height);

	scale = sf::Vector2f(map->getSize().x / (Map::getCountTile().x * Map::getTileSize()),
		map->getSize().y / (Map::getCountTile().y * Map::getTileSize()));
	setTilesScale();
	cutTiles();
}

bool mapInMenu::exit()
{
	return !active;
}

void mapInMenu::drawActive()
{
	toControl();
	setPlayerVisible();

	draw();

	for (const auto &i : navigation)
	{
		renderSprites::Instance().addToRender(i.first->text);
		renderSprites::Instance().addToRender(i.second);
	}

	for (const auto &i : tag)
		renderSprites::Instance().addToRender(i);

	renderSprites::Instance().addToRender(centerOfTag);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		active = false;

		map->setSize(mapSizeUnactive);
		map->setPosition(mapPosUnactive);

		cutTiles();

		playerIsVisible = 2;
	}
}

void mapInMenu::drawUnactive()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)))
	{
		active = true;

		map->setSize(mapSizeActive);
		map->setPosition(menuPos);

		scale = sf::Vector2f(0.3f, 0.3f);
		setTilesScale();
		centerMapOnPlayer();
		cutTiles();

		canSetTarget = false;

		tag[0]->setPosition(menuPos.x + window->getSize().x / 2.f, menuPos.y + window->getSize().y / 2.f + 5.f);
		tag[1]->setPosition(menuPos.x + window->getSize().x / 2.f - 5.f, menuPos.y + window->getSize().y / 2.f);
		tag[2]->setPosition(menuPos.x + window->getSize().x / 2.f, menuPos.y + window->getSize().y / 2.f - 5.f);
		tag[3]->setPosition(menuPos.x + window->getSize().x / 2.f + 5.f, menuPos.y + window->getSize().y / 2.f);

		centerOfTag->setPosition(tag[3]->getPosition().x - 5.f, tag[3]->getPosition().y);
	}

	draw();
}

void mapInMenu::setPlayerPosition(Tile *playerTile, const sf::Vector2f &lengthFromTileOrigin, const float &rot)
{
	this->playerTile = playerTile;
	this->lengthFromTileOrigin = lengthFromTileOrigin;
	playerRotation = rot;

	if (targetIsSet)
		setTarget();
}

bool mapInMenu::isActive()
{
	return active;
}

void mapInMenu::toControl()
{
	const float movingValue = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		mapTiles[0][0]->getTileMapSprite()->getPosition().y < centerOfTag->getPosition().y)
	{
		if (centerOfTag->getPosition().y - movingValue >= mapTiles[0][0]->getTileMapSprite()->getPosition().y)
			moveAllTiles(sf::Vector2f(0, movingValue));
		else
			moveAllTiles(sf::Vector2f(0, centerOfTag->getPosition().y - mapTiles[0][0]->getTileMapSprite()->getPosition().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getPosition().y + mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getGlobalBounds().height > centerOfTag->getPosition().y)
	{
		if (centerOfTag->getPosition().y + movingValue <= mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getPosition().y + mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getGlobalBounds().height)
			moveAllTiles(sf::Vector2f(0, -movingValue));
		else
			moveAllTiles(sf::Vector2f(0, -(mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getPosition().y + mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getGlobalBounds().height - centerOfTag->getPosition().y)));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		mapTiles[0][0]->getTileMapSprite()->getPosition().x < centerOfTag->getPosition().x)
	{
		if (centerOfTag->getPosition().x - movingValue >= mapTiles[0][0]->getTileMapSprite()->getPosition().x)
			moveAllTiles(sf::Vector2f(movingValue, 0));
		else
			moveAllTiles(sf::Vector2f(centerOfTag->getPosition().x - mapTiles[0][0]->getTileMapSprite()->getPosition().x, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getPosition().x + mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getGlobalBounds().width > centerOfTag->getPosition().x)
	{
		if (centerOfTag->getPosition().x + movingValue <= mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getPosition().x + mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getGlobalBounds().width)
			moveAllTiles(sf::Vector2f(-movingValue, 0));
		else
			moveAllTiles(sf::Vector2f(-(mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getPosition().x + mapTiles[static_cast<size_t>(Map::getCountTile().y - 1)][static_cast<size_t>(Map::getCountTile().x - 1)]->getTileMapSprite()->getGlobalBounds().width - centerOfTag->getPosition().x), 0));
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		canSetTarget = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canSetTarget)
	{
		if (targetIsSet)
			targetIsSet = false;
		else if (!targetIsSet)
		{
			targetIsSet = true;



			setTarget();

		}
		canSetTarget = false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && canSetTarget)
	{
		if (targetIsSet)
			targetIsSet = false;
		else if (!targetIsSet)
		{
			targetIsSet = true;



			setTarget();

		}
		canSetTarget = false;
	}

	const float zoomValue = 0.05f;

	if ((*Game::getScrollValue() > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) && scale.x < maxScale->x && scale.y < maxScale->y)
	{
		auto tileSprite = getCenterTileOnWindow()->getTileMapSprite();
		sf::Vector2f lengthFromTile = centerOfTag->getPosition() - tileSprite->getPosition();
		scale = sf::Vector2f(scale.x + zoomValue, scale.y + zoomValue);
		setTilesScale();
		centerMapOnTile(tileSprite, lengthFromTile);
	}
	else if ((*Game::getScrollValue() < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) && scale.x > minScale->x && scale.y > minScale->y)
	{
		auto tileSprite = getCenterTileOnWindow()->getTileMapSprite();
		sf::Vector2f lengthFromTile = centerOfTag->getPosition() - tileSprite->getPosition();
		scale = sf::Vector2f(scale.x - zoomValue, scale.y - zoomValue);
		setTilesScale();
		centerMapOnTile(tileSprite,lengthFromTile);
	}
	*Game::getScrollValue() = 0;
}

bool mapInMenu::mouseOnMap()
{
	if (map->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
		return true;
	return false;
}

Tile * mapInMenu::getCenterTileOnWindow()
{
	auto tileLeftUpCornerOfMap = Map::getTilesVector()[0][0];

	size_t y = (centerOfTag->getPosition().y - tileLeftUpCornerOfMap->getTileMapSprite()->getPosition().y) / tileLeftUpCornerOfMap->getTileMapSprite()->getGlobalBounds().height;
	
	if (y > Map::getCountTile().y - 1)
		y = Map::getCountTile().y - 1;
	else if (y < 0)
		y = 0;

	size_t x = (centerOfTag->getPosition().x - tileLeftUpCornerOfMap->getTileMapSprite()->getPosition().x) / tileLeftUpCornerOfMap->getTileMapSprite()->getGlobalBounds().width;

	if (x > Map::getCountTile().x - 1)
		x = Map::getCountTile().x - 1;
	else if (x < 0)
		x = 0;

	return Map::getTilesVector()[y][x];
}

void mapInMenu::centerMapOnTile(sf::Sprite *tileSprite, const sf::Vector2f &lengthFromTile)
{
	sf::Vector2f moveOffset = sf::Vector2f((map->getPosition().x + map->getGlobalBounds().width / 2.f) - (tileSprite->getPosition().x + lengthFromTile.x * scale.x),
	(map->getPosition().y + map->getGlobalBounds().height / 2.f) - (tileSprite->getPosition().y + lengthFromTile.y * scale.y));

	moveAllTiles(moveOffset);
}

void mapInMenu::centerMapOnPlayer()
{
	sf::Vector2f moveOffset = sf::Vector2f((map->getPosition().x + map->getGlobalBounds().width / 2.f) - (playerTile->getTileMapSprite()->getPosition().x + lengthFromTileOrigin.x * scale.x),
		(map->getPosition().y + map->getGlobalBounds().height / 2.f) - (playerTile->getTileMapSprite()->getPosition().y + lengthFromTileOrigin.y * scale.y));

	moveAllTiles(moveOffset);
}

void mapInMenu::moveAllTiles(const sf::Vector2f & offset)
{
	for (size_t i = 0;i < Map::getCountTile().y;++i)
		for (size_t j = 0;j < Map::getCountTile().x;++j)
			mapTiles[i][j]->getTileMapSprite()->move(offset);

	updateIcons();
}

void mapInMenu::updateIcons()
{
	player->setPosition(sf::Vector2f(playerTile->getTileMapSprite()->getPosition().x + lengthFromTileOrigin.x * scale.x,
		playerTile->getTileMapSprite()->getPosition().y + lengthFromTileOrigin.y * scale.y));
	player->setRotation(playerRotation);
}

void mapInMenu::setTilesScale()
{
	for (size_t i = 0;i < Map::getCountTile().y;++i)
		for (size_t j = 0;j < Map::getCountTile().x;++j)
		{
			auto tile = mapTiles[i][j]->getTileMapSprite();
			tile->setScale(scale);
			tile->setPosition(map->getPosition().x + j * (Map::getTileSize() * scale.x), map->getPosition().y + i * (Map::getTileSize() * scale.y));
		}

	updateIcons();
}

void mapInMenu::cutTiles()
{
	for (size_t i = 0;i < Map::getCountTile().y;++i)
		for (size_t j = 0;j < Map::getCountTile().x;++j)
		{
			auto tile = mapTiles[i][j]->getTileMapSprite();

			// reset
			tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Map::getTileSize(), Map::getTileSize())));

			if (!active && map->getGlobalBounds().intersects(tile->getGlobalBounds()))
			{
				if (map->getGlobalBounds().contains(tile->getPosition()) &&
					map->getGlobalBounds().contains(tile->getPosition().x + tile->getGlobalBounds().width, tile->getPosition().y) &&
					map->getGlobalBounds().contains(tile->getPosition().x + tile->getGlobalBounds().width, tile->getPosition().y + tile->getGlobalBounds().height) &&
					map->getGlobalBounds().contains(tile->getPosition().x, tile->getPosition().y + tile->getGlobalBounds().height))

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Map::getTileSize(), Map::getTileSize())));


				// upper border

				if (map->getPosition().y > tile->getPosition().y &&
					map->getPosition().y < tile->getPosition().y + tile->getGlobalBounds().height)
				{
					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, static_cast<int>(map->getPosition().y - tile->getPosition().y)),
						sf::Vector2i(Map::getTileSize(), static_cast<int>(Map::getTileSize() - (map->getPosition().y - tile->getPosition().y)))));
					tile->move(0, map->getPosition().y - tile->getPosition().y);
				}

				// bottom border

				else if (map->getPosition().y + map->getGlobalBounds().height > tile->getPosition().y &&
					map->getPosition().y + map->getPosition().y + map->getGlobalBounds().height < tile->getPosition().y + tile->getGlobalBounds().height)

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
						sf::Vector2i(Map::getTileSize(), static_cast<int>(Map::getTileSize() - ((tile->getPosition().y + tile->getGlobalBounds().height) - (map->getPosition().y + map->getGlobalBounds().height))))));

				// left border

				if (map->getPosition().x > tile->getPosition().x &&
					map->getPosition().x < tile->getPosition().x + tile->getGlobalBounds().width)
				{
					tile->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>(map->getPosition().x - tile->getPosition().x), 0),
						sf::Vector2i(static_cast<int>(Map::getTileSize() - (map->getPosition().x - tile->getPosition().x)), Map::getTileSize())));
					tile->move(map->getPosition().x - tile->getPosition().x, 0);
				}

				// right border

				else if (map->getPosition().x + map->getGlobalBounds().width > tile->getPosition().x &&
					map->getPosition().x + map->getGlobalBounds().width < tile->getPosition().x + tile->getGlobalBounds().width)

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
						sf::Vector2i(static_cast<int>(Map::getTileSize() - ((tile->getPosition().x + tile->getGlobalBounds().width) - (map->getPosition().x + map->getGlobalBounds().width))), Map::getTileSize())));
			}
		}
}

void mapInMenu::draw()
{
	for (size_t i = 0;i<Map::getCountTile().y;++i)
		for (size_t j = 0;j<Map::getCountTile().x;++j)
			if (map->getGlobalBounds().intersects(mapTiles[i][j]->getTileMapSprite()->getGlobalBounds()))
				renderSprites::Instance().addToRender(mapTiles[i][j]->getTileMapSprite());

	if (map->getGlobalBounds().contains(player->getPosition()) && playerIsVisible)
		renderSprites::Instance().addToRender(player);

	if (map->getGlobalBounds().contains(target->getPosition()) && targetIsSet)
		renderSprites::Instance().addToRender(target);
}

void mapInMenu::setPlayerVisible()
{
	if (time.time->asSeconds() >= 0.25)
	{
		time.clock->restart();
		*time.time = sf::Time::Zero;

		if (playerIsVisible <= 0)
			playerIsVisible = 2;
		else
			playerIsVisible--;
	}
}

void mapInMenu::setTarget()
{

}