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

	textureOfMap = new sf::RenderTexture;
	textureOfMiniMap = new sf::RenderTexture;
	sf::RenderTexture textureOfHitboxGrass;

	textureOfMap->create(mapSize->x, mapSize->y);
	textureOfMiniMap->create(mapSize->x, mapSize->y);
	textureOfHitboxGrass.create(mapSize->x, mapSize->y);

	textureOfMap->clear();
	textureOfMiniMap->clear();
	textureOfHitboxGrass.clear();

	for (int i = 0; i<*tilesCountHeigth; i++)
	{
		std::vector<Tile*>buf;
		for (int j = 0; j < *tilesCountWidth; j++)
		{
			int a;
			file >> a;
			sf::Sprite *spriteMap = tilesManager::Instance().getTilesMap(a);
			spriteMap->setPosition(j * *TileSize, i * *TileSize);
			textureOfMap->draw(*spriteMap);

			sf::Sprite *spriteMiniMap = tilesManager::Instance().getTilesMiniMap(a);
			spriteMiniMap->setPosition(j * *TileSize, i * *TileSize);
			textureOfMiniMap->draw(*spriteMiniMap);

			sf::Sprite *spriteHitbox = tilesManager::Instance().getTilesHitboxGrass(a);
			spriteHitbox->setPosition(j * *TileSize, i * *TileSize);
			textureOfHitboxGrass.draw(*spriteHitbox);

			buf.push_back(new Tile(a, sf::Vector2f(static_cast<float>(j * *TileSize), static_cast<float>(i * *TileSize))));
		}
		Tiles.push_back(buf);
	}

	// adding buildings on map

	textureOfMap->display();
	textureOfMiniMap->display();
	textureOfHitboxGrass.display();

	file.clear();
	file.close();

	map = new sf::Sprite(textureOfMap->getTexture());
	radar = new sf::Sprite(textureOfMiniMap->getTexture());
	hitboxGrass = new sf::Image(textureOfHitboxGrass.getTexture().copyToImage());

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

	delete map;
	delete textureOfMap;
	delete hitboxGrass;

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

	map->setTextureRect(sf::IntRect(sf::Vector2i(view->getCenter().x - view->getSize().x / 2 - 10, view->getCenter().y - view->getSize().y / 2 - 10),
		sf::Vector2i(view->getSize().x + 10,view->getSize().y + 10)));

	map->setPosition(sf::Vector2f(view->getCenter().x - view->getSize().x / 2 - 10, view->getCenter().y - view->getSize().y / 2 - 10));
}

void Map::drawUnder()
{
	renderSprites::Instance().addToRender(map);

	if (allCarSingleTraces.size() > 600 * allCarSingleTraces.size())
	{
		for (auto i = 0;i < 10;++i)
			delete allCarSingleTraces[i].first;

		allCarSingleTraces.erase(allCarSingleTraces.begin(), allCarSingleTraces.begin() + 10);
	}

	for (size_t i = 0;i<allCarSingleTraces.size();i++)
	{
		if (allCarSingleTraces[i].second <= 0 &&
			Map::isOutsideView(sf::Vector2f(allCarSingleTraces[i].first->getGlobalBounds().left + allCarSingleTraces[i].first->getGlobalBounds().width,
				allCarSingleTraces[i].first->getGlobalBounds().top + allCarSingleTraces[i].first->getGlobalBounds().height)))
		{
			delete allCarSingleTraces[i].first;
			allCarSingleTraces.erase(allCarSingleTraces.begin() + i, allCarSingleTraces.begin() + i + 1);
			--i;
		}
		else if (!Map::isOutsideView(sf::Vector2f(allCarSingleTraces[i].first->getGlobalBounds().left + allCarSingleTraces[i].first->getGlobalBounds().width,
			allCarSingleTraces[i].first->getGlobalBounds().top + allCarSingleTraces[i].first->getGlobalBounds().height)))

			renderSprites::Instance().addToRender(allCarSingleTraces[i].first);
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

sf::Sprite * Map::getRadar()
{
	return Instance().radar;
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

	if (Instance().hitboxGrass->getPixel(static_cast<unsigned>(pos.x),static_cast<unsigned>(pos.y)) == sf::Color::White)
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