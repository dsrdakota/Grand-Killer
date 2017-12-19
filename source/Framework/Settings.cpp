#include "Settings.hpp"
#include "../Game.hpp"
#include "Error.hpp"

#include <fstream>
#include <string>

Settings::Settings()
{
	doubles.clear();
	bools.clear();
}

int Settings::parseFile()
{
	std::ifstream file("game.cfg");
	if (!file.good())
		return 1; // Error

	else
	{
		std::string line, section = "";
		while (getline(file, line))
		{
			std::string name = "", data = "";

			if (line.length() <= 0)
				continue;

			else if (line[0] == '[' && line[line.length() - 1] == ']') // It's section
			{
				section = line.substr(1, line.length() - 2);
				continue;
			}

			else
			{
				name = line.substr(0, line.find('='));
				data = line.substr(line.find('=') + 1, line.length());
			}

			if (isBool(data))
				bools[section][name] = data == "true" ? true : false;

			else
				doubles[section][name] = std::stoi(data);
		}
	}
	file.clear();
	file.close();
	return 0; 
}

bool Settings::isBool(const std::string &data)
{
	if (data == "true" || data == "false")
		return true;
	return false;
}