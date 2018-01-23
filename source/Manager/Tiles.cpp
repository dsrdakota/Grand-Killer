#include "Tiles.hpp"
#include "Texture.hpp"

#include <fstream>

tilesManager::tilesManager()
{
	std::ifstream file("data/Map/Tileset/TilesPath.txt"); // binary soon

	std::string line;
	while (file >> line)
		TilesPath.push_back(line);

	file.clear();
	file.close();

	for (int i = 0; i < 78; i++)
	{
		textureManager::load(std::to_string(i), TilesPath[i]);
		// zaladowanie hitboxa trawy
	}
}

tilesManager::~tilesManager()
{

}

std::vector<Tile*> tilesManager::getOnlyGrassTiles()
{
	return allGrassTile;
}

void tilesManager::addTileToGrassVector(Tile* tile)
{
	allGrassTile.push_back(tile);
}