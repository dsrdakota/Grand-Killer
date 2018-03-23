#include "Minimap.hpp"

#include "../Game.hpp"

#include "../Engine/Engine.hpp"
#include "../Map/ObjectsManager/Tiles.hpp"
#include "../Map/Radar.hpp"

Minimap::Minimap()
{
	window = Game::Instance().getWindow();

	mapTiles = TilesManager::getTilesVector();

	map = new sf::Sprite;
	mapArea = new sf::RectangleShape;

	maxScale = new sf::Vector2f(0.8f, 0.8f);
	minScale = new sf::Vector2f(0.15f, 0.15f);

	background = new sf::RectangleShape(static_cast<sf::Vector2f>(window->getSize()));
	background->setFillColor(sf::Color(1, 36, 3, 200));

	player = new sf::Sprite(*TextureManager::get("playerMinimap"));
	player->setOrigin(player->getGlobalBounds().left + player->getGlobalBounds().width / 2.f, player->getGlobalBounds().top + player->getGlobalBounds().height / 2.f);

	target = new sf::Sprite(*TextureManager::get("targetMinimap"));
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

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PUNKT TRASY"), KeysManager::Instance().getKeySprite(KeysManager::Keys::Enter)));
	navigation[0].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "WROC"), KeysManager::Instance().getKeySprite(KeysManager::Keys::Esc)));
	navigation[1].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), KeysManager::Instance().getKeySprite(KeysManager::Keys::D)));
	navigation[2].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), KeysManager::Instance().getKeySprite(KeysManager::Keys::A)));
	navigation[3].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), KeysManager::Instance().getKeySprite(KeysManager::Keys::S)));
	navigation[4].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "PORUSZANIE KAMERA"), KeysManager::Instance().getKeySprite(KeysManager::Keys::W)));
	navigation[5].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 0, ""), KeysManager::Instance().getKeySprite(KeysManager::Keys::PageDown)));
	navigation[6].second->setScale(0.9f, 0.9f);

	navigation.push_back(std::make_pair(new Text(sf::Color::White, 10, "ZOOM"), KeysManager::Instance().getKeySprite(KeysManager::Keys::PageUp)));
	navigation[7].second->setScale(0.9f, 0.9f);
}

Minimap::~Minimap()
{
	delete map;
	delete mapArea;
	delete player;

	delete target;
	delete cursor;

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

void Minimap::setPosition()
{
	map->setTexture(*Radar::getRadarSprite()->getTexture());

	mapArea->setSize(static_cast<sf::Vector2f>(window->getSize()));

	navigation[0].second->setPosition(window->getSize().x - navigation[0].second->getGlobalBounds().width - 40,
		window->getSize().y - navigation[0].second->getGlobalBounds().height - 15);
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

	canSetTarget = false;
	scale = sf::Vector2f(0.4f, 0.4f);

	tag[0]->setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f + 6.f);
	tag[1]->setPosition(window->getSize().x / 2.f - 6.f, window->getSize().y / 2.f);
	tag[2]->setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f - 6.f);
	tag[3]->setPosition(window->getSize().x / 2.f + 6.f, window->getSize().y / 2.f);

	centerOfTag->setPosition(tag[3]->getPosition().x - 6.f, tag[3]->getPosition().y);

	resetCooldown();
}

void Minimap::show(bool fromMenu)
{
	toControl();
	setPlayerVisible();

	if (!fromMenu)
		Painter::Instance().addToInterfaceDraw(background);

	Painter::Instance().addToInterfaceDraw(map);

	if (mapArea->getGlobalBounds().contains(player->getPosition()) && playerIsVisible)
		Painter::Instance().addToInterfaceDraw(player);

	if (mapArea->getGlobalBounds().contains(target->getPosition()) && targetIsSet)
		Painter::Instance().addToInterfaceDraw(target);

	for (const auto &i : navigation)
	{
		Painter::Instance().addToInterfaceDraw(i.first->text);
		Painter::Instance().addToInterfaceDraw(i.second);
	}

	for (const auto &i : tag)
		Painter::Instance().addToInterfaceDraw(i);
}

bool Minimap::canExitMinimap()
{
	return cooldown.clock->getElapsedTime().asSeconds() > 0.5f;
}

bool Minimap::canRunMinimap()
{
	return cooldown.clock->getElapsedTime().asSeconds() > 0.5f;
}

void Minimap::resetCooldown()
{
	cooldown.clock->restart();
	*cooldown.time = sf::Time::Zero;
}

const bool Minimap::isTargetSet()
{
	return targetIsSet;
}

const sf::Vector2f & Minimap::getTargetPos()
{
	return target->getPosition();
}

void Minimap::setPlayerPosition(Tile *playerTile, const sf::Vector2f &lengthPlayerFromTileOrigin, const float &rot)
{
	this->playerTile = playerTile;
	this->lengthPlayerFromTileOrigin = lengthPlayerFromTileOrigin;
	playerRotation = rot;

	setTilesScale();
	centerMapOnPlayer();
}

void Minimap::toControl()
{
	const float movingValue = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		mapTiles[0][0]->getTileMiniMapSprite()->getPosition().y < centerOfTag->getPosition().y)
	{
		if (centerOfTag->getPosition().y - movingValue >= mapTiles[0][0]->getTileMiniMapSprite()->getPosition().y)
			moveAllTiles(sf::Vector2f(0, movingValue));
		else
			moveAllTiles(sf::Vector2f(0, centerOfTag->getPosition().y - mapTiles[0][0]->getTileMiniMapSprite()->getPosition().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getPosition().y + mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getGlobalBounds().height > centerOfTag->getPosition().y)
	{
		if (centerOfTag->getPosition().y + movingValue <= mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getPosition().y + mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getGlobalBounds().height)
			moveAllTiles(sf::Vector2f(0, -movingValue));
		else
			moveAllTiles(sf::Vector2f(0, -(mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getPosition().y + mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getGlobalBounds().height - centerOfTag->getPosition().y)));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		mapTiles[0][0]->getTileMiniMapSprite()->getPosition().x < centerOfTag->getPosition().x)
	{
		if (centerOfTag->getPosition().x - movingValue >= mapTiles[0][0]->getTileMiniMapSprite()->getPosition().x)
			moveAllTiles(sf::Vector2f(movingValue, 0));
		else
			moveAllTiles(sf::Vector2f(centerOfTag->getPosition().x - mapTiles[0][0]->getTileMiniMapSprite()->getPosition().x, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getPosition().x + mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getGlobalBounds().width > centerOfTag->getPosition().x)
	{
		if (centerOfTag->getPosition().x + movingValue <= mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getPosition().x + mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getGlobalBounds().width)
			moveAllTiles(sf::Vector2f(-movingValue, 0));
		else
			moveAllTiles(sf::Vector2f(-(mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getPosition().x + mapTiles[static_cast<size_t>(TilesManager::getCountTile().y - 1)][static_cast<size_t>(TilesManager::getCountTile().x - 1)]->getTileMiniMapSprite()->getGlobalBounds().width - centerOfTag->getPosition().x), 0));
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		canSetTarget = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canSetTarget)
	{
		if (targetIsSet)
		{
			targetIsSet = false;
			Radar::Instance().resetTexture();
			map->setTexture(*Radar::getRadarSprite()->getTexture());
		}
		else if (!targetIsSet)
		{
			targetIsSet = true;

			targetTile = getTileUnderMouse();
			lengthTargetFromTileOrigin = static_cast<sf::Vector2f>(static_cast<sf::Vector2f>(sf::Mouse::getPosition())) - targetTile->getTileMiniMapSprite()->getPosition();

			setTarget();
		}
		canSetTarget = false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && canSetTarget)
	{
		if (targetIsSet)
		{
			targetIsSet = false;
			Radar::Instance().resetTexture();
			map->setTexture(*Radar::getRadarSprite()->getTexture());
		}
		else if (!targetIsSet)
		{
			targetIsSet = true;

			targetTile = getCenterTileOnWindow();
			lengthTargetFromTileOrigin = centerOfTag->getPosition() - targetTile->getTileMiniMapSprite()->getPosition();

			setTarget();
		}
		canSetTarget = false;
	}

	const float zoomValue = 0.05f;

	if ((*Game::getScrollValue() > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) && scale.x < maxScale->x && scale.y < maxScale->y)
	{
		auto tileSprite = getCenterTileOnWindow()->getTileMiniMapSprite();
		sf::Vector2f lengthFromTile = centerOfTag->getPosition() - tileSprite->getPosition();
		scale = sf::Vector2f(scale.x + zoomValue, scale.y + zoomValue);
		setTilesScale();
		centerMapOnTile(tileSprite, lengthFromTile);
	}
	else if ((*Game::getScrollValue() < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) && scale.x > minScale->x && scale.y > minScale->y)
	{
		auto tileSprite = getCenterTileOnWindow()->getTileMiniMapSprite();
		sf::Vector2f lengthFromTile = centerOfTag->getPosition() - tileSprite->getPosition();
		scale = sf::Vector2f(scale.x - zoomValue, scale.y - zoomValue);
		setTilesScale();
		centerMapOnTile(tileSprite, lengthFromTile);
	}
	*Game::getScrollValue() = 0;
}

bool Minimap::mouseOnMap()
{
	if (mapArea->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		return true;
	return false;
}

Tile * Minimap::getCenterTileOnWindow()
{
	return getTileUnderPosition(centerOfTag->getPosition());
}

Tile * Minimap::getTileUnderMouse()
{
	return getTileUnderPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition()));
}

Tile * Minimap::getTileUnderPosition(const sf::Vector2f & position)
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

void Minimap::centerMapOnTile(sf::Sprite *tileSprite, const sf::Vector2f &lengthFromTile)
{
	sf::Vector2f moveOffset = sf::Vector2f((mapArea->getPosition().x + mapArea->getGlobalBounds().width / 2.f) - (tileSprite->getPosition().x + lengthFromTile.x),
		(mapArea->getPosition().y + mapArea->getGlobalBounds().height / 2.f) - (tileSprite->getPosition().y + lengthFromTile.y));

	moveAllTiles(moveOffset);
}

void Minimap::centerMapOnPlayer()
{
	sf::Vector2f moveOffset = sf::Vector2f((mapArea->getPosition().x + mapArea->getGlobalBounds().width / 2.f) - (playerTile->getTileMiniMapSprite()->getPosition().x + lengthPlayerFromTileOrigin.x * scale.x),
		(mapArea->getPosition().y + mapArea->getGlobalBounds().height / 2.f) - (playerTile->getTileMiniMapSprite()->getPosition().y + lengthPlayerFromTileOrigin.y * scale.y));

	moveAllTiles(moveOffset);
}

void Minimap::moveAllTiles(const sf::Vector2f & offset)
{
	for (size_t i = 0;i < TilesManager::getCountTile().y;++i)
		for (size_t j = 0;j < TilesManager::getCountTile().x;++j)
			mapTiles[i][j]->getTileMiniMapSprite()->move(offset);

	updateIcons();
}

void Minimap::updateIcons()
{
	map->setPosition(mapTiles[0][0]->getTileMiniMapSprite()->getPosition());

	player->setPosition(sf::Vector2f(playerTile->getTileMiniMapSprite()->getPosition().x + lengthPlayerFromTileOrigin.x * scale.x,
		playerTile->getTileMiniMapSprite()->getPosition().y + lengthPlayerFromTileOrigin.y * scale.y));
	player->setRotation(playerRotation);

	if (targetIsSet)
		setTarget();
}

void Minimap::setTilesScale()
{
	for (size_t i = 0;i < TilesManager::getCountTile().y;++i)
		for (size_t j = 0;j < TilesManager::getCountTile().x;++j)
		{
			auto tile = mapTiles[i][j]->getTileMiniMapSprite();
			tile->setScale(scale);
			tile->setPosition(mapArea->getPosition().x + j * (TilesManager::getTileSize() * scale.x), mapArea->getPosition().y + i * (TilesManager::getTileSize() * scale.y));
		}

	map->setScale(scale);
	updateIcons();
}

void Minimap::setPlayerVisible()
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

void Minimap::setTarget()
{
	target->setPosition(sf::Vector2f(targetTile->getTileMiniMapSprite()->getPosition().x + lengthTargetFromTileOrigin.x,
		targetTile->getTileMiniMapSprite()->getPosition().y + lengthTargetFromTileOrigin.y));
}