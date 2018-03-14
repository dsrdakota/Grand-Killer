#include "CarConfig.hpp"

#include <fstream>

CarConfig::~CarConfig()
{
	for (const auto &i : savedCars)
		for (const auto &j : hitboxes[i])
			for (const auto &hitbox : j)
				delete hitbox;
}

void CarConfig::loadCarConfig(const std::string &carName)
{
	Instance().savedCars.push_back(carName);
	loadMovementConfig(carName);
	loadTurnConfig(carName);
	loadHitboxConfig(carName);
}

double CarConfig::getValue(const std::string &carName, const std::string & valueName)
{
	return Instance().values[carName][valueName];
}

std::vector<std::vector<sf::CircleShape*>> CarConfig::getHitboxes(const std::string &carName)
{
	return Instance().hitboxes[carName];
}

void CarConfig::loadMovementConfig(const std::string &carName)
{
	std::string lowerCarName = carName;
	std::transform(lowerCarName.begin(), lowerCarName.end(), lowerCarName.begin(), ::tolower);
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".movement");

	double value;
	file >> value;
	Instance().values[carName]["MAX_SPEED"] = value;
	file >> value;
	Instance().values[carName]["acceleration"] = value;
	file >> value;
	Instance().values[carName]["breakingForce"] = value;
	file >> value;
	Instance().values[carName]["typeOfDrive"] = value;

	file.clear();
	file.close();
}

void CarConfig::loadTurnConfig(const std::string &carName)
{
	std::string lowerCarName = carName;
	std::transform(lowerCarName.begin(), lowerCarName.end(), lowerCarName.begin(), ::tolower);
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".turn");

	double value;
	file >> value;
	Instance().values[carName]["SPEED_ROTATE_CAR"] = value;
	file >> value;
	Instance().values[carName]["SPEED_ROTATE_TIRE"] = value;

	file.clear();
	file.close();
}

void CarConfig::loadHitboxConfig(const std::string &carName)
{
	std::string lowerCarName = carName;
	std::transform(lowerCarName.begin(), lowerCarName.end(), lowerCarName.begin(), ::tolower);
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".hitbox");

	file.clear();
	file.close();
}
