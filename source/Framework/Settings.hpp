#pragma once

#include <unordered_map>

class Settings
{
public:
	Settings();

	template <typename T>
	T giveMeValue(const std::string &section, const std::string &name, const T &want)
	{
		if (sizeof(want) == sizeof(double))
			return doubles[section][name];

		return bools[section][name];
	}
	int parseFile();

private:
	bool isBool(const std::string &data);

	std::unordered_map < std::string, std::unordered_map<std::string, int>>doubles;
	std::unordered_map < std::string, std::unordered_map<std::string, bool>>bools;
};