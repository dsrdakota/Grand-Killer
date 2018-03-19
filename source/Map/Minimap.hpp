#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Engine.hpp"
#include "ObjectsManager/Tiles.hpp"

class Minimap
{
public:

	~Minimap();

	Minimap(const Minimap &) = delete;
	void operator=(const Minimap &) = delete;

	inline static Minimap& Instance()
	{
		static Minimap minimap;
		return minimap;
	}

private:

	sf::RenderWindow *window;

	Minimap();
};