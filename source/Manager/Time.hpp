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


class trailerTime
{
public:

	inline static trailerTime& Instance()
	{
		static trailerTime time;
		return time;
	}

	inline static sf::Time getTime() { return *trailerTime::Instance().time->time; }

	inline static void getTimetoClock() { *trailerTime::Instance().time->time = trailerTime::Instance().time->clock->getElapsedTime(); }

	inline static void reset() { *trailerTime::Instance().time->time = sf::Time::Zero; trailerTime::Instance().time->clock->restart(); }

	inline static void DeleteTrailerTime() { delete trailerTime::Instance().time; }

private:
	inline trailerTime() { time = new Time; }

	Time *time;
};