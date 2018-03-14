#include "Config.hpp"

#include <fstream>
#include <string>

double Config::giveMeValue(const std::string & section, const std::string & name)
{
	auto searchSection = doubles.find(section);
	if (searchSection == doubles.end())
		return 0.0;
	else
	{
		auto searchName = doubles[section].find(name);
		if (searchName == doubles[section].end())
			return 0.0;
	}
	return doubles[section][name];
}

int Config::parseFile()
{
	std::ifstream file("game.cfg");
	if (!file.good())
		createConfigFile();
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
			doubles[section][name] = std::stoi(data);
		}
	}

	file.clear();
	file.close();

	if (doubles.size() < 1)
		return -1;

	return 1; 
}

void Config::createConfigFile()
{
	std::ofstream file("game.cfg");

	file << "\n\n[GENERAL]\n";
	file << "Fps=60\n";
	doubles["GENERAL"]["FPS"] = 60;
	file << "Width=1366\n";
	doubles["GENERAL"]["Width"] = 1366;
	file << "Height=768\n";
	doubles["GENERAL"]["Height"] = 768;
	file << "Colors=32\n";
	doubles["GENERAL"]["Colors"] = 32;
	file << "WindowMode=0\n";
	doubles["GENERAL"]["WindowMode"] = 0;
	file << "AntialiasingLevel=8\n";
	doubles["GENERAL"]["AntialiasingLevel"] = 8;
	file << "VerticalSync=1";
	doubles["GENERAL"]["VerticalSync"] = 1;
}