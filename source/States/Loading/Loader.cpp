#include "Loader.hpp"

#include "../../Map/MapsManager.hpp"

#include <fstream>

bool Loader::play()
{
	isError = false;

	unsigned amountOfFiles = carsName.size() * carTextures1.size() + carTextures2.size() + carTextures3.size() + textureWithName.size() + otherTextures.size() + mapTiles.size() + /* minimapTiles*/56 + carsName.size() * carsConfigFiles.size();

	text = new Text(sf::Color::White, 50, "Loader ( to change ), files to load: " + std::to_string(amountOfFiles));

	text->text->setPosition(window->getSize().x / 2 - text->text->getGlobalBounds().width / 2,
		window->getSize().y / 2 - text->text->getGlobalBounds().height / 2);

	loadText = new Text(sf::Color::Red, 40, "Loading file: path");

	loadText->text->setPosition(text->text->getPosition().x, text->text->getPosition().y + text->text->getGlobalBounds().height + 10);

	loadCarTextures1();

	drawLoadingText("Creating map...");
	MapsManager::Instance().init();

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

			auto result = TextureManager::load(path.substr(path.find_last_of('/') + 1, path.find_last_of('.')), path);

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
	auto load = [&](const std::vector<std::string> &textures) {
		for (const auto &j : textures)
		{
			drawLoadingText(j);

			auto result = TextureManager::load(j.substr(j.find_last_of('/') + 1, j.find_last_of('.')), j);

			if (!result)
			{
				error(j);
				return;
			}
		}
	};

	if (!isError)
		load(carTextures3);

	if (!isError)
		loadMapTiles();
}

void Loader::loadMapTiles()
{
	unsigned count = 0;
	for (const auto &i : mapTiles)
	{
		if (i.find("_G") == std::string::npos)
		{
			drawLoadingText(i);
			auto result = TextureManager::load(std::to_string(count), i);

			if (!result)
			{
				error(i);
				return;
			}
			// only asphalt or grass tile
			if (count == 0 ||
				count == 64 || 
				!((count >= 29 && count <= 34) ||
				(count >= 59 && count <= 63) ||
				count > 64))
			{

				std::string pathToMinimap = i;
				pathToMinimap.replace(pathToMinimap.find("Tileset"), 7, "Minimap");
				drawLoadingText("Loading: " + pathToMinimap);

				result = TextureManager::load(std::to_string(count) + "_Minimap", pathToMinimap);

				if (!result)
				{
					error(pathToMinimap);
					return;
				}
			}

			count++;
		}
		else // its a grass hitbox
		{
			drawLoadingText("Loading: " + i);

			auto result = TextureManager::load(std::to_string(count) + "_Hitbox", i);

			if (!result)
			{
				error(i);
				return;
			}
		}
	}

	loadOtherTextures();
}

void Loader::loadOtherTextures()
{
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