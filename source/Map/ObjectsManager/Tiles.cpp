#include "Tiles.hpp"
#include "../../Engine/Engine.hpp"

#include <fstream>

TilesManager::TilesManager()
{
	TileSize = new const short int(80);
	tilesCountWidth = new const short int(75);
	tilesCountHeigth = new const short int(75);

	countOfTilesType = new const unsigned(78);
	std::string line;

	std::ifstream file("data/Map/Tileset/Tiles.txt"); // binary soon

	for (int i = 0; i< *tilesCountHeigth; i++)
	{
		std::vector<Tile*>buf;
		std::vector<sf::Sprite*>MapBuf;
		std::vector<sf::Sprite*>MiniMapBuf;
		std::vector<sf::Sprite*>GrassBuf;
		for (int j = 0; j < *tilesCountWidth; j++)
		{
			int a;
			file >> a;

			MapBuf.push_back(new sf::Sprite(*TextureManager::get(std::to_string(a))));
			MapBuf[MapBuf.size() - 1]->setPosition(sf::Vector2f(static_cast<float>(j * *TileSize), static_cast<float>(i * *TileSize)));

			MiniMapBuf.push_back(new sf::Sprite(*TextureManager::get(std::to_string(a) + "_Minimap")));
			MiniMapBuf[MiniMapBuf.size() - 1]->setPosition(sf::Vector2f(static_cast<float>(j * *TileSize), static_cast<float>(i * *TileSize)));

			GrassBuf.push_back(new sf::Sprite(*TextureManager::get(std::to_string(a) + "_Hitbox")));
			GrassBuf[GrassBuf.size() - 1]->setPosition(sf::Vector2f(static_cast<float>(j * *TileSize), static_cast<float>(i * *TileSize)));

			buf.push_back(new Tile(a, sf::Vector2f(static_cast<float>(j * *TileSize), static_cast<float>(i * *TileSize))));
		}
		Tiles.push_back(buf);

		TilesMap.push_back(MapBuf);
		TilesMiniMap.push_back(MiniMapBuf);
		TilesHitboxGrass.push_back(GrassBuf);
	}

	file.clear();
	file.close();
}

TilesManager::~TilesManager()
{
	delete TileSize;
	delete tilesCountHeigth;
	delete tilesCountWidth;

	for (const auto &i : TilesMap)
		for(const auto &j:i)
			delete j;

	for (const auto &i : TilesMiniMap)
		for (const auto &j : i)
			delete j;
	
	for (const auto &i : TilesHitboxGrass)
		for (const auto &j : i)
			delete j;
}

std::vector<std::vector<sf::Sprite*>> TilesManager::getTileMapVector()
{
	return Instance().TilesMap;
}

std::vector<std::vector<sf::Sprite*>> TilesManager::getTileMiniMapVector()
{
	return Instance().TilesMiniMap;
}

std::vector<std::vector<sf::Sprite*>> TilesManager::getTileHitboxGrassVector()
{
	return Instance().TilesHitboxGrass;
}

std::vector<std::vector<Tile*>>& TilesManager::getTilesVector()
{
	return Instance().Tiles;
}