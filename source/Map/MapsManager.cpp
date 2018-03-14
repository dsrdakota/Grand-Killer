#include "MapsManager.hpp"

#include <fstream>

MapsManager::MapsManager()
{
	Tiles::Instance();
}

void MapsManager::init()
{
	mainmap = new Mainmap;
	//minimap = new Minimap;
	//radar = new Radar;
	loadMapFromFile();

	mainmap->updateMap();
}

MapsManager::~MapsManager()
{
	delete mainmap;
	delete minimap;
	delete radar;
}

void MapsManager::loadMapFromFile()
{
	std::ifstream file("data/Map/Tileset/Tiles.txt"); // binary soon

	for (unsigned i = 0; i < Tiles::getTilesCount().y; i++)
	{
		for (unsigned j = 0; j < Tiles::getTilesCount().x; j++)
		{
			int type;
			file >> type;

			addTile(static_cast<Tiles::Types>(type), sf::Vector2f(j * static_cast<float>(Tiles::getTileSize().x), i * static_cast<float>(Tiles::getTileSize().y)));
		}
	}

	file.clear();
	file.close();
}

void MapsManager::addTile(const Tiles::Types &type, const sf::Vector2f & position)
{
	mainmap->getTiles()[static_cast<unsigned>(position.x) / Tiles::getTileSize().y][static_cast<unsigned>(position.y) / Tiles::getTileSize().x]->setTexture(*TextureManager::get(std::to_string(static_cast<int>(type))));
	mainmap->getTiles()[static_cast<unsigned>(position.x) / Tiles::getTileSize().y][static_cast<unsigned>(position.y) / Tiles::getTileSize().x]->setPosition(position);

	//sf::Sprite *minimapSprite = new sf::Sprite;
	
	/*if (static_cast<int>(type) == 0 ||
		(static_cast<int>(type) >= 29 && static_cast<int>(type) <= 34) ||
		(static_cast<int>(type) >= 59 && static_cast<int>(type) <= 63))
		minimapSprite->setTexture(*TextureManager::get(std::to_string(static_cast<int>(Tiles::Types::asphalt)) + "_Minimap"));

	else if (static_cast<int>(type) >= 64)
		minimapSprite->setTexture(*TextureManager::get(std::to_string(static_cast<int>(Tiles::Types::grass)) + "_Minimap"));

	else
		minimapSprite->setTexture(*TextureManager::get(std::to_string(static_cast<int>(type)) + "_Minimap"));
	
	sf::Sprite *radarSprite = new sf::Sprite;

	minimapSprite->setPosition(position);

	*radarSprite = *minimapSprite;

	Instance().minimap->getTiles()[static_cast<unsigned>(position.y) / *Instance().TileSize].push_back(minimapSprite);
	Instance().radar->getTiles()[static_cast<unsigned>(position.y) / *Instance().TileSize].push_back(radarSprite);*/
}


Mainmap * MapsManager::getMainmap()
{
	return Instance().mainmap;
}

Minimap * MapsManager::getMinimap()
{
	return Instance().minimap;
}

Radar * MapsManager::getRadar()
{
	return Instance().radar;
}
