#include "Map.hpp"

#include "../Game.hpp"

#include <fstream>

Map::Map() : window(Game::Instance().getWindow())
{
	TilesManager::Instance();
}

Map::~Map()
{
	window->setView(window->getDefaultView());

	delete map;
	delete textureOfMap;
	delete hitboxGrass;

	//delete otherElements;
	//delete trafficSigns;
	//delete trafficLights;
}

void Map::init()
{
	view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(window->getSize()));

	mapSize = new sf::Vector2f(6000, 6000);

	textureOfMap = new sf::RenderTexture;

	sf::RenderTexture textureOfHitboxGrass;

	textureOfMap->create(static_cast<unsigned>(mapSize->x), static_cast<unsigned>(mapSize->y));
	textureOfHitboxGrass.create(static_cast<unsigned>(mapSize->x), static_cast<unsigned>(mapSize->y));

	auto mapTiles = TilesManager::getTileMapVector();
	auto grassHitboxTiles = TilesManager::getTileHitboxGrassVector();

	textureOfMap->clear();
	textureOfHitboxGrass.clear();

	for (int i = 0; i< TilesManager::getCountTile().y; i++)
	{
		for (int j = 0; j < TilesManager::getCountTile().x; j++)
		{
			textureOfMap->draw(*mapTiles[i][j]);

			textureOfHitboxGrass.draw(*grassHitboxTiles[i][j]);
		}
	}

	textureOfMap->display();
	textureOfHitboxGrass.display();

	map = new sf::Sprite(textureOfMap->getTexture());
	hitboxGrass = new sf::Image(textureOfHitboxGrass.getTexture().copyToImage());

	/*std::ifstream file("data/Map/Tileset/Tiles.txt"); // binary soon

	textureOfMap = new sf::RenderTexture;
	textureOfMiniMap = new sf::RenderTexture;
	sf::RenderTexture textureOfHitboxGrass;

	textureOfMap->create(static_cast<unsigned>(mapSize->x), static_cast<unsigned>(mapSize->y));
	textureOfMiniMap->create(static_cast<unsigned>(mapSize->x), static_cast<unsigned>(mapSize->y));
	textureOfHitboxGrass.create(static_cast<unsigned>(mapSize->x), static_cast<unsigned>(mapSize->y));

	textureOfMap->clear();
	textureOfMiniMap->clear();
	textureOfHitboxGrass.clear();

	for (int i = 0; i< TilesManager::getCountTile().y; i++)
	{
		std::vector<Tile*>buf;
		for (int j = 0; j < TilesManager::getCountTile().x; j++)
		{
			int a;
			file >> a;
			sf::Sprite *spriteMap = TilesManager::Instance().getTilesMap(a);
			spriteMap->setPosition(j * static_cast<float>(TilesManager::getTileSize()), i * static_cast<float>(TilesManager::getTileSize()));
			textureOfMap->draw(*spriteMap);

			sf::Sprite *spriteMiniMap = TilesManager::Instance().getTilesMiniMap(a);
			spriteMiniMap->setPosition(j * static_cast<float>(TilesManager::getTileSize()), i * static_cast<float>(TilesManager::getTileSize()));
			textureOfMiniMap->draw(*spriteMiniMap);

			sf::Sprite *spriteHitbox = TilesManager::Instance().getTilesHitboxGrass(a);
			spriteHitbox->setPosition(j * static_cast<float>(TilesManager::getTileSize()), i * static_cast<float>(TilesManager::getTileSize()));
			textureOfHitboxGrass.draw(*spriteHitbox);

			buf.push_back(new Tile(a, sf::Vector2f(static_cast<float>(j * TilesManager::getTileSize()), static_cast<float>(i * TilesManager::getTileSize()))));
		}
		Tiles.push_back(buf);
	}

	// adding buildings on mapArea

	textureOfMap->display();
	textureOfMiniMap->display();
	textureOfHitboxGrass.display();

	file.clear();
	file.close();

	map = new sf::Sprite(textureOfMap->getTexture());
	radar = new sf::Sprite(textureOfMiniMap->getTexture());
	hitboxGrass = new sf::Image(textureOfHitboxGrass.getTexture().copyToImage());*/

	//otherElements = new Other;
	//trafficSigns = new TrafficSigns;
	//trafficLights = new TrafficLights;
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

	map->setTextureRect(sf::IntRect(sf::Vector2i(view->getCenter().x - view->getSize().x / 2 - 10, view->getCenter().y - view->getSize().y / 2 - 10),
		sf::Vector2i(view->getSize().x + 10, view->getSize().y + 10)));

	map->setPosition(sf::Vector2f(view->getCenter().x - view->getSize().x / 2 - 10, view->getCenter().y - view->getSize().y / 2 - 10));
}

void Map::drawUnder()
{
	Painter::Instance().addToDraw(map);

	if (allCarSingleTraces.size() > 600 * allCarSingleTraces.size())
	{
		for (auto i = 0;i < 10;++i)
		{
			delete allCarSingleTraces[i].first;
			delete allCarSingleTraces[i].second;
		}

		allCarSingleTraces.erase(allCarSingleTraces.begin(), allCarSingleTraces.begin() + 10);
	}

	for (size_t i = 0;i<allCarSingleTraces.size();i++)
	{
		if (*allCarSingleTraces[i].second <= 0 &&
			Map::isOutsideView(sf::Vector2f(allCarSingleTraces[i].first->getGlobalBounds().left + allCarSingleTraces[i].first->getGlobalBounds().width,
				allCarSingleTraces[i].first->getGlobalBounds().top + allCarSingleTraces[i].first->getGlobalBounds().height)))
		{
			delete allCarSingleTraces[i].first;
			delete allCarSingleTraces[i].second;
			allCarSingleTraces.erase(allCarSingleTraces.begin() + i, allCarSingleTraces.begin() + i + 1);
			--i;
		}
		else if (!Map::isOutsideView(sf::Vector2f(allCarSingleTraces[i].first->getGlobalBounds().left + allCarSingleTraces[i].first->getGlobalBounds().width,
			allCarSingleTraces[i].first->getGlobalBounds().top + allCarSingleTraces[i].first->getGlobalBounds().height)))

			Painter::Instance().addToDraw(allCarSingleTraces[i].first);
	}

	updateTimeInTrace();
}

void Map::drawOn()
{
	
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
	if (pos.x < 0 || pos.y < 0)
		return false;

	if (pos.x > Instance().mapSize->x || pos.y > Instance().mapSize->y)
		return false;

	if (Instance().hitboxGrass->getPixel(static_cast<unsigned>(pos.x), static_cast<unsigned>(pos.y)) == sf::Color::White)
		return true;

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

void Map::updateTimeInTrace()
{
	auto &traces = Map::Instance().getAllCarTraces();

	if (clock.time->asSeconds() > 1)
	{
		for (auto &i : traces)
			if (*i.second > 0)
				(*i.second)--;

		clock.clock->restart();
		*clock.time = clock.time->Zero;
	}
}