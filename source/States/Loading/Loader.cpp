#include "Loader.hpp"

#include "../../Map/ObjectsManager/Tiles.hpp"

#include "../../Map/Map.hpp"
#include "../../Map/Radar.hpp"
#include "../../Map/Minimap.hpp"
#include "../../Map/GPS/GPS.hpp"

#include <fstream>

// i think its to change, too many repeted

bool Loader::play()
{
	isError = false;

	unsigned amountOfFiles = carsName.size() * carTextures1.size() + carTextures2.size() + carDoors.size() * carsName.size() + textureWithName.size() + otherTextures.size() + 113 + /* minimapTiles*/56 + carsName.size() * carsConfigFiles.size();

	text = new Text(sf::Color::White, 50, "Loader ( to change ), files to load: " + std::to_string(amountOfFiles));

	text->text->setPosition(window->getSize().x / 2 - text->text->getGlobalBounds().width / 2,
		window->getSize().y / 2 - text->text->getGlobalBounds().height / 2);

	loadText = new Text(sf::Color::Red, 40, "Loading file: path");

	loadText->text->setPosition(text->text->getPosition().x, text->text->getPosition().y + text->text->getGlobalBounds().height + 10);

	loadCarTextures1();

	if (!isError)
	{
		drawLoadingText("Creating map...");

		TilesManager::Instance();
		Map::Instance();
		Minimap::Instance();
		Radar::Instance();
		GPS::Instance();
	}

	return !isError;
}

void Loader::loadCarTextures1()
{
	for (const auto &i : carsName)
	{
		for (const auto &j : carTextures1)
		{
			std::string path = j;
			path.replace(path.find("carName"), 7, i);

			drawLoadingText(path);

			auto result = TextureManager::load(i + '_' + path.substr(path.find_last_of('/') + 1, path.find(".gk") - path.find_last_of('/') - 1), path);

			if (!result)
			{
				error(path);
				return;
			}
		}
	}
	loadCarTextures2();
}

void Loader::loadCarTextures2()
{
	for (const auto &j : carTextures2)
	{
		drawLoadingText(j);

		auto result = TextureManager::load(j.substr(j.find_last_of('/') + 1, j.find(".gk") - j.find_last_of('/') - 1), j);

		if (!result)
		{
			error(j);
			return;
		}
	}

	loadCarDoors();
}

void Loader::loadCarDoors()
{
	for (const auto &i : carsName)
	{
		for (const auto &j : carDoors)
		{
			std::string path = j;
			path.replace(path.find("carName"), 7, i);

			drawLoadingText(path);

			auto result = TextureManager::load(i + '_' + path.substr(path.find_last_of('/') + 1, path.find(".gk") - path.find_last_of('/') - 1), path);

			if (!result)
			{
				error(path);
				return;
			}
		}
	}

	loadMapTiles();
}

void Loader::loadMapTiles()
{
	std::ifstream file("data/Map/Tileset/TilesPath.txt"); // binary soon

	unsigned countOfTilesType = 78;
	std::string line;

	for (unsigned i = 0;i<countOfTilesType;++i)
	{
		file >> line;

		drawLoadingText(line);

		auto result = TextureManager::load(std::to_string(i), line);

		if (!result)
		{
			error(line);
			return;
		}

		std::string pathToTileMinimap = "data/Map/Minimap/" + line.substr(line.find_last_of('/') + 1);

		if (i == 0 ||
			(i >= 29 && i <= 34) ||
			(i >= 59 && i <= 63))
		{
			drawLoadingText("data/Map/Minimap/asphalt.gk");

			result = TextureManager::load(std::to_string(i) + "_Minimap", "data/Map/Minimap/asphalt.gk");

			if (!result)
			{
				error("data/Map/Minimap/asphalt.gk");
				return;
			}
		}

		else if (i >= 64)
		{
			drawLoadingText("data/Map/Minimap/grass.gk");

			result = TextureManager::load(std::to_string(i) + "_Minimap", "data/Map/Minimap/grass.gk");

			if (!result)
			{
				error("data/Map/Minimap/grass.gk");
				return;
			}
		}

		else
		{
			drawLoadingText(pathToTileMinimap);

			result = TextureManager::load(std::to_string(i) + "_Minimap", pathToTileMinimap);

			if (!result)
			{
				error(pathToTileMinimap);
				return;
			}
		}

		if (line.find("grass") != std::string::npos)
		{
			drawLoadingText(line.substr(0, line.find(".")) + "_G.gk");

			result = TextureManager::load(std::to_string(i) + "_Hitbox", line.substr(0, line.find(".")) + "_G.gk");

			if (!result)
			{
				error(line.substr(0, line.find(".")) + "_G.gk");
				return;
			}
		}

		else
		{
			drawLoadingText("data/Map/Tileset/asphalt_G.gk");

			result = TextureManager::load(std::to_string(i) + "_Hitbox", "data/Map/Tileset/asphalt_G.gk");

			if (!result)
			{
				error("data/Map/Tileset/asphalt_G.gk");
				return;
			}
		}
	}

	file.clear();
	file.close();

	loadOtherTextures();
}

void Loader::loadOtherTextures()
{
	for (const auto &j : otherTextures)
	{
		drawLoadingText(j);

		auto result = TextureManager::load(j.substr(j.find_last_of('/') + 1, j.find(".gk") - j.find_last_of('/') -1), j);

		if (!result)
		{
			error(j);
			return;
		}
	}

	loadTexturesWithName();
}

void Loader::loadTexturesWithName()
{
	for (const auto &i : textureWithName)
	{
		drawLoadingText("Loading: " + i.first);

		auto result = TextureManager::load(i.first, i.second);

		if (!result)
		{
			error(i.second);
			return;
		}
	}
	checkCarsConfigFiles();
}

void Loader::checkCarsConfigFiles()
{
	for (const auto &i : carsName)
	{
		for (const auto &j : carsConfigFiles)
		{
			std::string path = j;
			path.replace(path.find("CARNAME"), 7, i);

			std::string carNameLower = i;
			std::transform(carNameLower.begin(), carNameLower.end(), carNameLower.begin(), ::tolower);

			path.replace(path.find("carname"), 7, carNameLower);

			drawLoadingText("Checking... " + path);

			std::fstream file(path);

			if (!file.good())
			{
				error(path);
				return;
			}

			file.clear();
			file.close();
		}
		CarConfig::loadCarConfig(i);
	}
	checkTxtFiles();
}

void Loader::checkTxtFiles()
{
	for (const auto &j : txtFiles)
	{
		drawLoadingText("Checking... " + j);

		std::fstream file(j);

		if (!file.good())
		{
			error(j);
			return;
		}

		file.clear();
		file.close();
	}

}

void Loader::drawLoadingText(const std::string & text)
{
	loadText->text->setString(text);

	if (game.getStatus() != Game::status::CleaningUp)
	{
		game.events();

		window->clear();

		window->draw(*this->text->text);
		window->draw(*loadText->text);

		window->display();
	}
}

void Loader::error(const std::string &path)
{
	loadText->text->setString("Can't open " + path + " [Q]");

	isError = true;

	while (game.getStatus() != Game::status::CleaningUp)
	{
		game.events();

		window->clear();

		window->draw(*text->text);
		window->draw(*loadText->text);

		window->display();
	}
}