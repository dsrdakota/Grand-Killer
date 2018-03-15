#include "mapInMenu.hpp"

mapInMenu::mapInMenu()
{
	map = new sf::Sprite;
	mapArea = new sf::RectangleShape;

	mapTiles = MapsManager::getMinimap()->getTiles();

	scale = sf::Vector2f(0, 0);
	maxScale = new sf::Vector2f(0.8f, 0.8f);
	minScale = new sf::Vector2f(0.15f, 0.15f);

	mapSizeActive = static_cast<sf::Vector2f>(window->getSize());

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

	active = false;

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

mapInMenu::~mapInMenu()
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

void mapInMenu::setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange)
{
	this->menuPos = menuPos;

	map->setTexture(*MapsManager::getRadar()->getMap()->getTexture());

	mapArea->setSize(sf::Vector2f(borderXrange.y - borderXrange.x, borderYrange.y - borderYrange.x));
	mapArea->setPosition(borderXrange.x, borderYrange.x);

	mapSizeUnactive = mapArea->getSize();
	mapPosUnactive = mapArea->getPosition();

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

	scale = sf::Vector2f(mapArea->getSize().x / (Tiles::getTilesCount().x * Tiles::getTileSize().x),
		mapArea->getSize().y / (Tiles::getTilesCount().y * Tiles::getTileSize().y));
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

	Painter::Instance().addToDraw(map);

	draw();

	for (const auto &i : navigation)
	{
		Painter::Instance().addToDraw(i.first->text);
		Painter::Instance().addToDraw(i.second);
	}

	for (const auto &i : tag)
		Painter::Instance().addToDraw(i);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		active = false;

		mapArea->setSize(mapSizeUnactive);
		mapArea->setPosition(mapPosUnactive);

		cutTiles();

		playerIsVisible = 2;
	}
}

void mapInMenu::drawUnactive()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (mouseOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)))
	{
		active = true;

		mapArea->setSize(mapSizeActive);
		mapArea->setPosition(menuPos);

		scale = sf::Vector2f(0.3f, 0.3f);
		setTilesScale();
		centerMapOnPlayer();
		cutTiles();

		canSetTarget = false;

		tag[0]->setPosition(menuPos.x + window->getSize().x / 2.f, menuPos.y + window->getSize().y / 2.f + 6.f);
		tag[1]->setPosition(menuPos.x + window->getSize().x / 2.f - 6.f, menuPos.y + window->getSize().y / 2.f);
		tag[2]->setPosition(menuPos.x + window->getSize().x / 2.f, menuPos.y + window->getSize().y / 2.f - 6.f);
		tag[3]->setPosition(menuPos.x + window->getSize().x / 2.f + 6.f, menuPos.y + window->getSize().y / 2.f);

		centerOfTag->setPosition(tag[3]->getPosition().x - 6.f, tag[3]->getPosition().y);
	}

	for (size_t i = 0;i<Tiles::getTilesCount().y;++i)
		for (size_t j = 0;j<Tiles::getTilesCount().x;++j)
			if (mapArea->getGlobalBounds().intersects(mapTiles[i][j]->getGlobalBounds()))
				Painter::Instance().addToDraw(mapTiles[i][j]);
	draw();
}

const bool mapInMenu::isTargetSet()
{
	return targetIsSet;
}

const sf::Vector2f & mapInMenu::getTargetPos()
{
	return target->getPosition();
}

void mapInMenu::setPlayerPosition(sf::Sprite *playerTile, const sf::Vector2f &lengthPlayerFromTileOrigin, const float &rot)
{
	this->playerTile = playerTile;
	this->lengthPlayerFromTileOrigin = lengthPlayerFromTileOrigin;
	playerRotation = rot;
}

bool mapInMenu::isActive()
{
	return active;
}

void mapInMenu::toControl()
{
	const float movingValue = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		mapTiles[0][0]->getPosition().y < centerOfTag->getPosition().y)
	{
		if (centerOfTag->getPosition().y - movingValue >= mapTiles[0][0]->getPosition().y)
			moveAllTiles(sf::Vector2f(0, movingValue));
		else
			moveAllTiles(sf::Vector2f(0, centerOfTag->getPosition().y - mapTiles[0][0]->getPosition().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getPosition().y + mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getGlobalBounds().height > centerOfTag->getPosition().y)
	{
		if (centerOfTag->getPosition().y + movingValue <= mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x- 1)]->getPosition().y + mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getGlobalBounds().height)
			moveAllTiles(sf::Vector2f(0, -movingValue));
		else
			moveAllTiles(sf::Vector2f(0, -(mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getPosition().y + mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getGlobalBounds().height - centerOfTag->getPosition().y)));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		mapTiles[0][0]->getPosition().x < centerOfTag->getPosition().x)
	{
		if (centerOfTag->getPosition().x - movingValue >= mapTiles[0][0]->getPosition().x)
			moveAllTiles(sf::Vector2f(movingValue, 0));
		else
			moveAllTiles(sf::Vector2f(centerOfTag->getPosition().x - mapTiles[0][0]->getPosition().x, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getPosition().x + mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getGlobalBounds().width > centerOfTag->getPosition().x)
	{
		if (centerOfTag->getPosition().x + movingValue <= mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getPosition().x + mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getGlobalBounds().width)
			moveAllTiles(sf::Vector2f(-movingValue, 0));
		else
			moveAllTiles(sf::Vector2f(-(mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getPosition().x + mapTiles[static_cast<size_t>(Tiles::getTilesCount().y - 1)][static_cast<size_t>(Tiles::getTilesCount().x - 1)]->getGlobalBounds().width - centerOfTag->getPosition().x), 0));
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

			targetTile = getTileUnderMouse();
			lengthTargetFromTileOrigin = static_cast<sf::Vector2f>(window->mapPixelToCoords(sf::Mouse::getPosition())) - targetTile->getPosition();

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

			targetTile = getCenterTileOnWindow();
			lengthTargetFromTileOrigin = centerOfTag->getPosition() - targetTile->getPosition();

			setTarget();

		}
		canSetTarget = false;
	}

	const float zoomValue = 0.05f;

	if ((*Game::getScrollValue() > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) && scale.x < maxScale->x && scale.y < maxScale->y)
	{
		auto tileSprite = getCenterTileOnWindow();
		sf::Vector2f lengthFromTile = centerOfTag->getPosition() - tileSprite->getPosition();
		scale = sf::Vector2f(scale.x + zoomValue, scale.y + zoomValue);
		setTilesScale();
		centerMapOnTile(tileSprite, lengthFromTile);
	}
	else if ((*Game::getScrollValue() < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) && scale.x > minScale->x && scale.y > minScale->y)
	{
		auto tileSprite = getCenterTileOnWindow();
		sf::Vector2f lengthFromTile = centerOfTag->getPosition() - tileSprite->getPosition();
		scale = sf::Vector2f(scale.x - zoomValue, scale.y - zoomValue);
		setTilesScale();
		centerMapOnTile(tileSprite, lengthFromTile);
	}
	*Game::getScrollValue() = 0;
}

bool mapInMenu::mouseOnMap()
{
	if (mapArea->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
		return true;
	return false;
}

sf::Sprite * mapInMenu::getCenterTileOnWindow()
{
	return getTileUnderPosition(centerOfTag->getPosition());
}

sf::Sprite * mapInMenu::getTileUnderMouse()
{
	return getTileUnderPosition(window->mapPixelToCoords(sf::Mouse::getPosition()));
}

sf::Sprite * mapInMenu::getTileUnderPosition(const sf::Vector2f & position)
{
	auto tileLeftUpCornerOfMap = MapsManager::getMainmap()->getTiles()[0][0];

	size_t y = static_cast<size_t>((position.y - tileLeftUpCornerOfMap->getPosition().y) / tileLeftUpCornerOfMap->getGlobalBounds().height);

	if (y > static_cast<size_t>(Tiles::getTilesCount().y) - 1)
		y = static_cast<size_t>(Tiles::getTilesCount().y) - 1;
	else if (y < 0)
		y = 0;

	size_t x = static_cast<size_t>((position.x - tileLeftUpCornerOfMap->getPosition().x) / tileLeftUpCornerOfMap->getGlobalBounds().width);

	if (x > static_cast<size_t>(Tiles::getTilesCount().x) - 1)
		x = static_cast<size_t>(Tiles::getTilesCount().x) - 1;
	else if (x < 0)
		x = 0;

	return MapsManager::getMainmap()->getTiles()[y][x];
}

void mapInMenu::centerMapOnTile(sf::Sprite *tileSprite, const sf::Vector2f &lengthFromTile)
{
	sf::Vector2f moveOffset = sf::Vector2f((mapArea->getPosition().x + mapArea->getGlobalBounds().width / 2.f) - (tileSprite->getPosition().x + lengthFromTile.x),
		(mapArea->getPosition().y + mapArea->getGlobalBounds().height / 2.f) - (tileSprite->getPosition().y + lengthFromTile.y));

	moveAllTiles(moveOffset);
}

void mapInMenu::centerMapOnPlayer()
{
	sf::Vector2f moveOffset = sf::Vector2f((mapArea->getPosition().x + mapArea->getGlobalBounds().width / 2.f) - (playerTile->getPosition().x + lengthPlayerFromTileOrigin.x * scale.x),
		(mapArea->getPosition().y + mapArea->getGlobalBounds().height / 2.f) - (playerTile->getPosition().y + lengthPlayerFromTileOrigin.y * scale.y));

	moveAllTiles(moveOffset);
}

void mapInMenu::moveAllTiles(const sf::Vector2f & offset)
{
	for (size_t i = 0;i < Tiles::getTilesCount().y;++i)
		for (size_t j = 0;j < Tiles::getTilesCount().x;++j)
			mapTiles[i][j]->move(offset);

	updateIcons();
}

void mapInMenu::updateIcons()
{
	map->setPosition(mapTiles[0][0]->getPosition());

	player->setPosition(sf::Vector2f(playerTile->getPosition().x + lengthPlayerFromTileOrigin.x * scale.x,
		playerTile->getPosition().y + lengthPlayerFromTileOrigin.y * scale.y));
	player->setRotation(playerRotation);

	if (targetIsSet)
		setTarget();
}

void mapInMenu::setTilesScale()
{
	for (size_t i = 0;i < Tiles::getTilesCount().y;++i)
		for (size_t j = 0;j < Tiles::getTilesCount().x;++j)
		{
			auto tile = mapTiles[i][j];
			tile->setScale(scale);
			tile->setPosition(mapArea->getPosition().x + j * (Tiles::getTileSize().x * scale.x), mapArea->getPosition().y + i * (Tiles::getTileSize().y * scale.y));
		}

	map->setScale(scale);
	updateIcons();
}

void mapInMenu::cutTiles()
{
	for (size_t i = 0;i < Tiles::getTilesCount().y;++i)
		for (size_t j = 0;j < Tiles::getTilesCount().x;++j)
		{
			auto tile = mapTiles[i][j];

			// reset
			tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Tiles::getTileSize().x, Tiles::getTileSize().y)));

			if (!active && mapArea->getGlobalBounds().intersects(tile->getGlobalBounds()))
			{
				if (mapArea->getGlobalBounds().contains(tile->getPosition()) &&
					mapArea->getGlobalBounds().contains(tile->getPosition().x + tile->getGlobalBounds().width, tile->getPosition().y) &&
					mapArea->getGlobalBounds().contains(tile->getPosition().x + tile->getGlobalBounds().width, tile->getPosition().y + tile->getGlobalBounds().height) &&
					mapArea->getGlobalBounds().contains(tile->getPosition().x, tile->getPosition().y + tile->getGlobalBounds().height))

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Tiles::getTileSize().x, Tiles::getTileSize().y)));


				// upper border

				if (mapArea->getPosition().y > tile->getPosition().y &&
					mapArea->getPosition().y < tile->getPosition().y + tile->getGlobalBounds().height)
				{
					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, static_cast<int>(mapArea->getPosition().y - tile->getPosition().y)),
						sf::Vector2i(Tiles::getTileSize().x, static_cast<int>(Tiles::getTileSize().y - (mapArea->getPosition().y - tile->getPosition().y)))));
					tile->move(0, mapArea->getPosition().y - tile->getPosition().y);
				}

				// bottom border

				else if (mapArea->getPosition().y + mapArea->getGlobalBounds().height > tile->getPosition().y &&
					mapArea->getPosition().y + mapArea->getPosition().y + mapArea->getGlobalBounds().height < tile->getPosition().y + tile->getGlobalBounds().height)

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
						sf::Vector2i(Tiles::getTileSize().x, static_cast<int>(Tiles::getTileSize().y - ((tile->getPosition().y + tile->getGlobalBounds().height) - (mapArea->getPosition().y + mapArea->getGlobalBounds().height))))));

				// left border

				if (mapArea->getPosition().x > tile->getPosition().x &&
					mapArea->getPosition().x < tile->getPosition().x + tile->getGlobalBounds().width)
				{
					tile->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>(mapArea->getPosition().x - tile->getPosition().x), 0),
						sf::Vector2i(static_cast<int>(Tiles::getTileSize().x - (mapArea->getPosition().x - tile->getPosition().x)), Tiles::getTileSize().y)));
					tile->move(mapArea->getPosition().x - tile->getPosition().x, 0);
				}

				// right border

				else if (mapArea->getPosition().x + mapArea->getGlobalBounds().width > tile->getPosition().x &&
					mapArea->getPosition().x + mapArea->getGlobalBounds().width < tile->getPosition().x + tile->getGlobalBounds().width)

					tile->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
						sf::Vector2i(static_cast<int>(Tiles::getTileSize().x - ((tile->getPosition().x + tile->getGlobalBounds().width) - (mapArea->getPosition().x + mapArea->getGlobalBounds().width))), Tiles::getTileSize().y)));
			}
		}
}

void mapInMenu::draw()
{
	if (mapArea->getGlobalBounds().contains(player->getPosition()) && playerIsVisible)
		Painter::Instance().addToDraw(player);

	if (mapArea->getGlobalBounds().contains(target->getPosition()) && targetIsSet)
		Painter::Instance().addToDraw(target);
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
	target->setPosition(sf::Vector2f(targetTile->getPosition().x + lengthTargetFromTileOrigin.x,
		targetTile->getPosition().y + lengthTargetFromTileOrigin.y));
}