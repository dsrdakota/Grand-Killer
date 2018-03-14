#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class CarConfig
{
public:

	~CarConfig();

	CarConfig(const CarConfig &) = delete;
	void operator=(const CarConfig &) = delete;

	static void loadCarConfig(const std::string &carName);
	static double getValue(const std::string &carName, const std::string &valueName);
	static std::vector<std::vector<sf::CircleShape*>> getHitboxes(const std::string &carName);

private:

	inline static CarConfig& Instance()
	{
		static CarConfig carConfig;
		return carConfig;
	}

	std::vector<std::string> savedCars;

	std::unordered_map<std::string, std::unordered_map<std::string, double>> values;
	std::unordered_map < std::string, std::vector<std::vector<sf::CircleShape*>>> hitboxes;

	CarConfig() { ; }

	static void loadMovementConfig(const std::string &carName);
	static void loadTurnConfig(const std::string &carName);
	static void loadHitboxConfig(const std::string &carName);
};