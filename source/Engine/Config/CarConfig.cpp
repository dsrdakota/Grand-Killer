#include "CarConfig.hpp"

#include <fstream>

CarConfig::~CarConfig()
{
	for (const auto &i : savedCars)
		for (const auto &j : hitboxVectors[i])
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

std::vector<sf::CircleShape*> CarConfig::getHitboxes(const std::string &carName)
{
	return Instance().hitboxes[carName];
}

std::vector<std::vector<sf::CircleShape*>> CarConfig::getHitboxVectors(const std::string & carName)
{
	return Instance().hitboxVectors[carName];
}

void CarConfig::loadMovementConfig(const std::string &carName)
{
	std::string lowerCarName = carName;
	std::transform(lowerCarName.begin(), lowerCarName.end(), lowerCarName.begin(), ::tolower);
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".movement"); // binary soon

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
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".turn"); // binary soon

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
	std::ifstream file("data/Models/Cars/" + carName + '/' + lowerCarName + ".hitbox", std::ios::binary);

	unsigned count;
	sf::Vector2f position;
	unsigned side;

	std::vector<sf::CircleShape*>frontHitboxes;
	std::vector<sf::CircleShape*>upRightHitboxes;
	std::vector<sf::CircleShape*>rightHitboxes;
	std::vector<sf::CircleShape*>downRightHitboxes;
	std::vector<sf::CircleShape*>backHitboxes;
	std::vector<sf::CircleShape*>downLeftHitboxes;
	std::vector<sf::CircleShape*>leftHitboxes;
	std::vector<sf::CircleShape*>upLeftHitboxes;

	std::vector<std::vector<sf::CircleShape*>> allHitboxInOneVector;
	std::vector<sf::CircleShape*>allHitboxes;

	std::unordered_map<std::string, sf::Vector2f>origins;

	setCarsOrigin(origins);

	file.read((char*)&count, sizeof(count));

	for (size_t i = 0; i < count; ++i)
	{
		file.read((char*)&position.x, sizeof(position.x));
		file.read((char*)&position.y, sizeof(position.y));
		file.read((char*)&side, sizeof(side));

		sf::CircleShape *hitbox = new sf::CircleShape(2);
		hitbox->setOrigin(origins[carName] - position + sf::Vector2f(hitbox->getRadius(), hitbox->getRadius()));

		allHitboxes.push_back(hitbox);

		switch (side)
		{
		case 0:
			frontHitboxes.push_back(hitbox);
			break;
		case 1:
			upRightHitboxes.push_back(hitbox);
			break;
		case 2:
			rightHitboxes.push_back(hitbox);
			break;
		case 3:
			downRightHitboxes.push_back(hitbox);
			break;
		case 4:
			backHitboxes.push_back(hitbox);
			break;
		case 5:
			downLeftHitboxes.push_back(hitbox);
			break;
		case 6:
			leftHitboxes.push_back(hitbox);
			break;
		case 7:
			upLeftHitboxes.push_back(hitbox);
			break;
		}
	}

	allHitboxInOneVector.push_back(frontHitboxes);
	allHitboxInOneVector.push_back(upRightHitboxes);
	allHitboxInOneVector.push_back(rightHitboxes);
	allHitboxInOneVector.push_back(downRightHitboxes);
	allHitboxInOneVector.push_back(backHitboxes);
	allHitboxInOneVector.push_back(downLeftHitboxes);
	allHitboxInOneVector.push_back(leftHitboxes);
	allHitboxInOneVector.push_back(upLeftHitboxes);

	Instance().hitboxVectors[carName] = allHitboxInOneVector;
	Instance().hitboxes[carName] = allHitboxes;

	file.clear();
	file.close();
}

void CarConfig::setCarsOrigin(std::unordered_map<std::string, sf::Vector2f>& origins)
{
	origins["Ambulance"] = sf::Vector2f(39, 107);
	origins["Audi"] = sf::Vector2f(48, 111);
	origins["Black_viper"] = sf::Vector2f(44, 111);
	origins["Car"] = sf::Vector2f(42, 105);
	origins["Mini_truck"] = sf::Vector2f(54, 116);
	origins["Police"] = sf::Vector2f(45, 110);
	origins["Taxi"] = sf::Vector2f(41, 99);
}
