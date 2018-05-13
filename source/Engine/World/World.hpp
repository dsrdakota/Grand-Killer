#pragma once

#include <SFML/Graphics.hpp>

class World
{
public:

	~World();

	World(const World &) = delete;
	void operator=(const World &) = delete;

	inline static World& Instance()
	{
		static World world;
		return world;
	}

	void simulate();

private:

	World();
};