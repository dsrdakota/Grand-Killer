#pragma once
#include "SFML/Graphics.hpp"

#include "../../Map/Map.hpp"

class Car;
class Traces
{
public:
	Traces(Car *car, const sf::CircleShape *tiresPos);

	void setTraces();

private:

	Car *car;

	const sf::CircleShape *tiresPos;

	bool isSameTraceOnVector(const sf::Vector2f &pos, const float &rot);
};
/*
class TracesThread
{
public:
	TracesThread()
	{
		running = new bool(false);
		result = new bool(false);
		from = new unsigned(false);
		howMany = new unsigned(false);
	}

	~TracesThread()
	{
		delete running;
		delete result;
		delete from;
		delete howMany;
	}

	void run()
	{
		while (true)
		{
			if (*running)
			{
				for (size_t i = *from; i<from + *howMany;++i)
					if (traces[i].first->getGlobalBounds().contains(pos) && traces[i].first->getRotation() == rot)
					{
						result = true;
						break;
					}
			}
		}
	}

	bool *running;
	bool *result;
	unsigned *from;
	unsigned *howMany;
};
*/