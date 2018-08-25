#include "CarConfig.hpp"

#include <fstream>
#include <iostream>

void CarConfig::loadCarConfig(const std::string &carName)
{
	Instance().savedCars.push_back(carName);
	loadMovementConfig(carName);
	loadTurnConfig(carName);
}

float CarConfig::getValue(const std::string &carName, const std::string & valueName)
{
	return Instance().values[carName][valueName];
}

void CarConfig::loadMovementConfig(const std::string &carName)
{
	std::string lowerCarName = carName;
	std::transform(lowerCarName.begin(), lowerCarName.end(), lowerCarName.begin(), ::tolower);
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".movement"); // binary soon

	float value;
	file >> value;

	if (carName == "Black viper")
		std::cout << value << std::endl;

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
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".turn"); // binary soon

	float value;
	file >> value;
	Instance().values[carName]["SPEED_ROTATE_CAR"] = value;
	file >> value;
	Instance().values[carName]["SPEED_ROTATE_TIRE"] = value;

	file.clear();
	file.close();
}
