#include "Map.hpp"

#include "../../../Manager/Texture.hpp"
#include "../../../Manager/renderSprites.hpp"
#include "../../../Game.hpp"

#include <fstream>

Map::Map() : window(Game::Instance().getWindow())
{
	//map = new sf::Sprite(*textureManager::load("background", "data/Map/map.png"));
	view = new sf::View(sf::Vector2f(100,100), sf::Vector2f(window->getSize()));

	TileSize = new const short int(80);
	MapWidth = new const short int(75);
	MapHeight = new const short int(75);

	FilePath ={ "data/Map/Tileset/asphalt.png",
		"data/Map/Tileset/asphalt_grass_corner_in_BL.png",
		"data/Map/Tileset/asphalt_grass_corner_in_BR.png",
		"data/Map/Tileset/asphalt_grass_corner_in_TL.png",
		"data/Map/Tileset/asphalt_grass_corner_in_TR.png",
		"data/Map/Tileset/asphalt_grass_corner_out_BL.png",
		"data/Map/Tileset/asphalt_grass_corner_out_BR.png",
		"data/Map/Tileset/asphalt_grass_corner_out_TL.png",
		"data/Map/Tileset/asphalt_grass_corner_out_TR.png",
		"data/Map/Tileset/asphalt_grass_hor_border_BOTT.png",
		"data/Map/Tileset/asphalt_grass_hor_border_LEFT.png",
		"data/Map/Tileset/asphalt_grass_hor_border_RIGHT.png",
		"data/Map/Tileset/asphalt_grass_hor_border_TOP.png",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_BL.png",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_BR.png",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_TL.png",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_TR.png",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_BL.png",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_BR.png",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_TL.png",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_TR.png",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_BL.png",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_BR.png",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_TL.png",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_TR.png",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_BL.png",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_BR.png",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_TL.png",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_TR.png",
		"data/Map/Tileset/asphalt_hor_lane_LEFT.png",
		"data/Map/Tileset/asphalt_hor_lane_RIGHT.png",
		"data/Map/Tileset/asphalt_hor_pedlanes.png",
		"data/Map/Tileset/asphalt_hor_pedlanes_LEFT.png",
		"data/Map/Tileset/asphalt_hor_pedlanes_RIGHT.png",
		"data/Map/Tileset/asphalt_manhole.png",
		"data/Map/Tileset/asphalt_pavement_corner_in_BL.png",
		"data/Map/Tileset/asphalt_pavement_corner_in_BR.png",
		"data/Map/Tileset/asphalt_pavement_corner_in_TL.png",
		"data/Map/Tileset/asphalt_pavement_corner_in_TR.png",
		"data/Map/Tileset/asphalt_pavement_corner_out_BL.png",
		"data/Map/Tileset/asphalt_pavement_corner_out_BR.png",
		"data/Map/Tileset/asphalt_pavement_corner_out_TL.png",
		"data/Map/Tileset/asphalt_pavement_corner_out_TR.png",
		"data/Map/Tileset/asphalt_pavement_hor_border_BOTT.png",
		"data/Map/Tileset/asphalt_pavement_hor_border_pedlanes_BOTT.png",
		"data/Map/Tileset/asphalt_pavement_hor_border_pedlanes_TL.png",
		"data/Map/Tileset/asphalt_pavement_hor_border_pedlanes_TOP.png",
		"data/Map/Tileset/asphalt_pavement_hor_border_TOP.png",
		"data/Map/Tileset/asphalt_pavement_hor_pedlanes_BL.png",
		"data/Map/Tileset/asphalt_pavement_hor_pedlanes_BR.png",
		"data/Map/Tileset/asphalt_pavement_hor_pedlanes_TR.png",
		"data/Map/Tileset/asphalt_pavement_vert_border_LEFT.png",
		"data/Map/Tileset/asphalt_pavement_vert_border_pedlanes_LEFT.png",
		"data/Map/Tileset/asphalt_pavement_vert_border_pedlanes_RIGHT.png",
		"data/Map/Tileset/asphalt_pavement_vert_border_RIGHT.png",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_BL.png",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_BR.png",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_TL.png",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_TR.png",
		"data/Map/Tileset/asphalt_vert_lane_BOTT.png",
		"data/Map/Tileset/asphalt_vert_lane_TOP.png",
		"data/Map/Tileset/asphalt_vert_pedlanes.png",
		"data/Map/Tileset/asphalt_vert_pedlanes_BOTT.png",
		"data/Map/Tileset/asphalt_vert_pedlanes_TOP.png",
		"data/Map/Tileset/grass.png",
		"data/Map/Tileset/grass_pavement_corner_in_BL.png",
		"data/Map/Tileset/grass_pavement_corner_in_BR.png",
		"data/Map/Tileset/grass_pavement_corner_in_TL.png",
		"data/Map/Tileset/grass_pavement_corner_in_TR.png",
		"data/Map/Tileset/grass_pavement_corner_out_BL.png",
		"data/Map/Tileset/grass_pavement_corner_out_BR.png",
		"data/Map/Tileset/grass_pavement_corner_out_TL.png",
		"data/Map/Tileset/grass_pavement_corner_out_TR.png",
		"data/Map/Tileset/grass_pavement_hor_border_BOTT.png",
		"data/Map/Tileset/grass_pavement_hor_border_TOP.png",
		"data/Map/Tileset/grass_pavement_vert_border_LEFT.png",
		"data/Map/Tileset/grass_pavement_vert_border_RIGHT.png",
		"data/Map/Tileset/pavement.png" };

	std::ifstream file("data/Map/Tileset/Tiles.txt");

	for (int i = 0; i<*MapHeight; i++)
	{
		std::vector<int>buf;
		for (int j = 0; j<*MapWidth; j++)
		{
			int a;
			file >> a;
			buf.push_back(a);
		}
		Tiles.push_back(buf);
	}

	for (int i = 0; i < 78; i++)
		textureManager::load(std::to_string(i), FilePath[i]);

	for (int i = 0; i<*MapHeight; i++)
	{
		for (int j = 0; j<*MapWidth; j++)
		{
			sf::Sprite *tile = new sf::Sprite;
			tile->setTexture(*textureManager::get(std::to_string(Tiles[i][j])));
			tile->setPosition(j * *TileSize, i * *TileSize);
			TileSprite.push_back(tile);
		}
	}

	grassHitbox = new sf::Image;
	grassHitbox->loadFromFile("data/Map/Hitboxes/grassHitbox.png");
	collisionHitbox = new sf::Image;
	collisionHitbox->loadFromFile("data/Map/Hitboxes/collisionHitbox.png");

	otherElements = new Other;
	trafficSigns = new TrafficSigns;
	trafficLights = new TrafficLights;
}

Map::~Map()
{
	window->setView(window->getDefaultView());
	//delete map;

	delete TileSize;
	delete MapHeight;
	delete MapWidth;

	delete grassHitbox;
	delete collisionHitbox;
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
	//view->setRotation(angle);
}

void Map::updateView(const sf::Vector2f &newerView)
{
	setView(newerView);

	if (view->getCenter().x - view->getSize().x / 2 < 0)
		setView(sf::Vector2f(view->getSize().x / 2, view->getCenter().y));

	else if (view->getCenter().x + view->getSize().x / 2 > 6000)
		setView(sf::Vector2f(6000 - view->getSize().x / 2, view->getCenter().y));

	if (view->getCenter().y - view->getSize().y / 2 < 0)
		setView(sf::Vector2f(view->getCenter().x, view->getSize().y / 2));

	else if (view->getCenter().y + view->getSize().y / 2 > 6000)
		setView(sf::Vector2f(view->getCenter().x, 6000 - view->getSize().y / 2));
	
}

void Map::drawUnder()
{
	//renderSprites::Instance().addToRender(map);


	for (const auto &i : TileSprite)
		renderSprites::Instance().addToRender(i);

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
		pos.y > viewPos.y - viewSize.y / 2  - 10 &&
		pos.y < viewPos.y + viewSize.y / 2 + 10)

		return false;

	return true;
}

bool Map::isPointOnGrass(const sf::Vector2f & pos)
{
	if (pos.x < 0 ||pos.y < 0)
		return false;

	if (Map::Instance().grassHitbox->getPixel(static_cast<unsigned>(pos.x),static_cast<unsigned>(pos.y)) == sf::Color(133, 91, 0))
		return true;

	return false;
}

bool Map::isPointInCollisionArea(const sf::Vector2f & pos)
{
	if (pos.x < 0 || pos.y < 0)
		return false;

	if (Map::Instance().collisionHitbox->getPixel(static_cast<unsigned>(pos.x), static_cast<unsigned>(pos.y)) == sf::Color(255, 0, 0))
		return true;
	return false;
}

sf::Vector2f Map::getUpLeftCornerPosOfCurrentView()
{
	auto &map = Instance();
	return sf::Vector2f(map.view->getCenter().x - map.view->getSize().x / 2,
		map.view->getCenter().y - map.view->getSize().y / 2);
}
