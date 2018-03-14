#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Time // aka clock
{
public:

	sf::Clock *clock;
	sf::Time *time;

	Time();

	~Time();
};

class TimeManager
{
public:

	static TimeManager* Instance();

	static void addToVector(Time* clockPtr);

	static std::vector<Time*> getVector();

	static void clearVector();

	static void getTimeOnClocks();

private:

	std::vector<Time*>allClocks;
};