#include "Map.hpp"

#include "../../Manager/Texture.hpp"
#include "../../Manager/renderSprites.hpp"
#include "../../Game.hpp"

#include <fstream>

Map::Map() : window(Game::Instance().getWindow())
{
	tilesManager::Instance();

	view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(window->getSize()));

	TileSize = new const short int(80);
	tilesCountWidth = new const short int(75);
	tilesCountHeigth = new const short int(75);

	mapSize = new sf::Vector2f(static_cast<float>(*TileSize * *tilesCountWidth), static_cast<float>(*TileSize * *tilesCountHeigth));

	std::ifstream file("data/Map/Tileset/Tiles.txt"); // binary soon

	for (int i = 0; i<*tilesCountHeigth; i++)
	{
		std::vector<Tile*>buf;
		for (int j = 0; j<*tilesCountWidth; j++)
		{
			int a;
			file >> a;
			buf.push_back(new Tile(a, sf::Vector2f(static_cast<float>(j * *TileSize), static_cast<float>(i * *TileSize))));
		}
		Tiles.push_back(buf);
	}

	file.clear();
	file.close();

	otherElements = new Other;
	trafficSigns = new TrafficSigns;
	trafficLights = new TrafficLights;
}

Map::~Map()
{
	window->setView(window->getDefaultView());

	delete TileSize;
	delete tilesCountHeigth;
	delete tilesCountWidth;

	for (const auto &i : Tiles)
		for (const auto &j : i)
			delete j;

	delete otherElements;
	delete trafficSigns;
	delete trafficLights;
}

void Map::setView(const sf::Vector2f & center)
{
	view->setCenter(center);
	window->setView(*view);
}

void Map::setRotation(const float & angle)
{
	view->setRotation(angle);
}

void Map::updateView(const sf::Vector2f &newerView)
{
	setView(newerView);

	if (view->getCenter().x - view->getSize().x / 2 < 0)
		setView(sf::Vector2f(view->getSize().x / 2, view->getCenter().y));

	else if (view->getCenter().x + view->getSize().x / 2 > mapSize->x)
		setView(sf::Vector2f(mapSize->x - view->getSize().x / 2, view->getCenter().y));

	if (view->getCenter().y - view->getSize().y / 2 < 0)
		setView(sf::Vector2f(view->getCenter().x, view->getSize().y / 2));

	else if (view->getCenter().y + view->getSize().y / 2 > mapSize->y)
		setView(sf::Vector2f(view->getCenter().x, mapSize->y - view->getSize().y / 2));

}

void Map::drawUnder()
{
	for (const auto &i : Tiles)
		for (const auto &j : i)
		{
			const auto &sprite = j->getTileSprite();
			if (!isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top)) ||
				!isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top)) ||
				!isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)) ||
				!isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)))
				renderSprites::Instance().addToRender(sprite);
		}

	if (allCarTraces.size() > 600 * allCarTraces.size())
	{
		for (auto i = 0;i < 10;++i)
			delete allCarTraces[i].first;

		allCarTraces.erase(allCarTraces.begin(), allCarTraces.begin() + 10);
	}

	for (size_t i = 0;i<allCarTraces.size();i++)
	{
		if (allCarTraces[i].second <= 0 &&
			Map::isOutsideView(sf::Vector2f(allCarTraces[i].first->getGlobalBounds().left + allCarTraces[i].first->getGlobalBounds().width,
				allCarTraces[i].first->getGlobalBounds().top + allCarTraces[i].first->getGlobalBounds().height)))
		{
			delete allCarTraces[i].first;
			allCarTraces.erase(allCarTraces.begin() + i, allCarTraces.begin() + i + 1);
			--i;
		}
		else if (!Map::isOutsideView(sf::Vector2f(allCarTraces[i].first->getGlobalBounds().left + allCarTraces[i].first->getGlobalBounds().width,
			allCarTraces[i].first->getGlobalBounds().top + allCarTraces[i].first->getGlobalBounds().height)))

			renderSprites::Instance().addToRender(allCarTraces[i].first);
	}

	//trafficSigns->drawUnder();

	//trafficLights->drawUnder();
}

void Map::drawOn()
{
	//otherElements->draw();

	//trafficSigns->drawOn();

	//trafficLights->drawOn();
}

bool Map::isOutsideView(const sf::Vector2f & pos)
{
	const sf::Vector2f viewSize = Map::Instance().view->getSize();
	const sf::Vector2f viewPos = Map::Instance().view->getCenter();

	if (pos.x > viewPos.x - viewSize.x / 2 - 10 &&
		pos.x < viewPos.x + viewSize.x / 2 + 10 &&
		pos.y > viewPos.y - viewSize.y / 2 - 10 &&
		pos.y < viewPos.y + viewSize.y / 2 + 10)

		return false;

	return true;
}

bool Map::isPointOnGrass(const sf::Vector2f & pos)
{
	auto allTileWithGrass = tilesManager::Instance().getOnlyGrassTiles();

	for (auto &i : allTileWithGrass)
	{
		if (i->getTileSprite()->getGlobalBounds().contains(pos))
		{
			if (static_cast<tilesManager::tileTypes>(i->getIndex()) == tilesManager::tileTypes::grass) // full grass
				return true;

			const sf::Image *hitbox = tilesManager::Instance().getTileGrassHitbox(i->getIndex());
			sf::Vector2f lengthFromTile = pos - i->getTileSprite()->getPosition();

			if (lengthFromTile.x >= 0 &&
				lengthFromTile.x < hitbox->getSize().x &&
				lengthFromTile.y >= 0 &&
				lengthFromTile.y < hitbox->getSize().y &&
				hitbox->getPixel(static_cast<unsigned>(lengthFromTile.x), static_cast<unsigned>(lengthFromTile.y)) == sf::Color::White)
				return true;
		}
	}
	return false;
}

bool Map::isPointInCollisionArea(const sf::Vector2f & pos)
{
	auto &map = Instance();
	if (pos.x < 0 || pos.x > map.mapSize->x)
		return true;
	if (pos.y < 0 || pos.y > map.mapSize->y)
		return true;

	// buildings

	return false;
}

sf::Vector2f Map::getUpLeftCornerPosOfCurrentView()
{
	auto &map = Instance();
	return sf::Vector2f(map.view->getCenter().x - map.view->getSize().x / 2,
		map.view->getCenter().y - map.view->getSize().y / 2);
}