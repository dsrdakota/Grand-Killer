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

		std::string pathToTileMinimap = "data/Map/Minimap/" + TilesPath[i].substr(TilesPath[i].find_last_of('/')+1);

		textureManager::load(std::to_string(i) + "_Minimap", pathToTileMinimap);

		if (TilesPath[i].find("grass") != std::string::npos)
		{
			sf::Image *image = new sf::Image;
			image->loadFromFile(TilesPath[i].substr(0, TilesPath[i].find(".")) + "_G.gif");
			grassTitlesHitbox.push_back(std::make_pair(image, new size_t(i)));
		}
	}
}

tilesManager::~tilesManager()
{
	for (const auto &i : grassTitlesHitbox)
	{
		delete i.first;
		delete i.second;
	}
}

std::vector<Tile*> tilesManager::getOnlyGrassTiles()
{
	return allGrassTile;
}

const sf::Image * tilesManager::getTileGrassHitbox(const size_t & index)
{
	for (const auto &i : grassTitlesHitbox)
		if (*i.second == index)
			return i.first;

	return nullptr;
}

void tilesManager::addTileToGrassVector(Tile* tile)
{
	allGrassTile.push_back(tile);
}