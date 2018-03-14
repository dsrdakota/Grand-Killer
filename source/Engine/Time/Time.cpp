#include "Time.hpp"

// Time ----------------

Time::Time()
{
	clock = new sf::Clock;
	time = new sf::Time;

	TimeManager::addToVector(this);
}

Time::~Time()
{
	delete clock;
	delete time;
}

// Time Manager --------

TimeManager * TimeManager::Instance()
{
	static TimeManager time;
	return &time;
}

void TimeManager::addToVector(Time * clockPtr)
{
	TimeManager::Instance()->allClocks.push_back(clockPtr);
}

std::vector<Time*> TimeManager::getVector()
{
	return TimeManager::Instance()->allClocks;
}

void TimeManager::clearVector()
{
	TimeManager::Instance()->allClocks.clear();
}

void TimeManager::getTimeOnClocks()
{
	for (const auto &i : TimeManager::Instance()->allClocks)
		*i->time = i->clock->getElapsedTime();
}