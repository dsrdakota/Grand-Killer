#pragma once

#include <unordered_map>

class Config
{
public:

	double giveMeValue(const std::string &section, const std::string &name);
	int parseFile();

private:

	std::unordered_map < std::string, std::unordered_map<std::string, int>>doubles;

	void createConfigFile();
};