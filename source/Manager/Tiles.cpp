#include "Tiles.hpp"
#include "Texture.hpp"

#include <fstream>

tilesManager::tilesManager()
{
	std::ifstream file("data/Map/Tileset/TilesPath.txt"); // binary soon

	countOfTiles = new const unsigned(78);
	std::string line;

	for(unsigned i=0;i<*countOfTiles;++i)
	{
		file >> line;

		TilesMap.push_back(new sf::Sprite(*textureManager::load(std::to_string(i), line)));

		std::string pathToTileMinimap = "data/Map/Minimap/" + line.substr(line.find_last_of('/') + 1);

		if (i == 0 ||
			(i >= 29 && i <= 34) ||
			(i >= 59 && i <= 63))
			TilesMiniMap.push_back(new sf::Sprite(*textureManager::load(std::to_string(i) + "_Minimap", "data/Map/Minimap/asphalt.png")));

		else if (i >= 64)
			TilesMiniMap.push_back(new sf::Sprite(*textureManager::load(std::to_string(i) + "_Minimap", "data/Map/Minimap/grass.png")));

		else
			TilesMiniMap.push_back(new sf::Sprite(*textureManager::load(std::to_string(i) + "_Minimap", pathToTileMinimap)));

		if (line.find("grass") != std::string::npos)
			TilesHitboxGrass.push_back(new sf::Sprite(*textureManager::load(std::to_string(i) + "_Hitbox", line.substr(0, line.find(".")) + "_G.gif")));
		else
			TilesHitboxGrass.push_back(new sf::Sprite(*textureManager::load(std::to_string(i) + "_Hitbox", "data/Map/Tileset/asphalt_G.gif")));
	}

	file.clear();
	file.close();
}

tilesManager::~tilesManager()
{
	for (const auto &i : TilesMap)
		delete i;

	for (const auto &i : TilesMiniMap)
		delete i;
	
	for (const auto &i : TilesHitboxGrass)
		delete i;
}

sf::Sprite * tilesManager::getTilesMap(const size_t & index)
{
	if (validateIndex(index))
		return TilesMap[index];
	return nullptr;
}

sf::Sprite * tilesManager::getTilesMiniMap(const size_t & index)
{
	if (validateIndex(index))
		return TilesMiniMap[index];
	return nullptr;
}

sf::Sprite * tilesManager::getTilesHitboxGrass(const size_t & index)
{
	if (validateIndex(index))
		return TilesHitboxGrass[index];
	return nullptr;
}

bool tilesManager::validateIndex(const size_t & index)
{
	if (index < 0)
		return false;
	
	if (index >= *countOfTiles)
		return false;

	return true;
}