#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class CarConfig
{
public:

	CarConfig(const CarConfig &) = delete;
	void operator=(const CarConfig &) = delete;

	static void loadCarConfig(const std::string &carName);
	static float getValue(const std::string &carName, const std::string &valueName);

private:

	inline static CarConfig& Instance()
	{
		static CarConfig carConfig;
		return carConfig;
	}

	std::vector<std::string> savedCars;

	std::unordered_map<std::string, std::unordered_map<std::string, float>> values;

	CarConfig() { ; }

	static void loadMovementConfig(const std::string &carName);
	static void loadTurnConfig(const std::string &carName);
};