#pragma once

#include <SFML/Graphics.hpp>

class Map
{
public:

	~Map();

	Map(const Map &) = delete;
	void operator=(const Map &) = delete;

	inline static Map& Instance()
	{
		static Map engine;
		return engine;
	}

	void setView(const sf::Vector2f &center);
	void updateView(const sf::Vector2f &newerView);
	void draw();

	static bool isOutsideView(const sf::Vector2f & pos);

	sf::Image* getGrassHitbox() { return grassHitbox; }

private:
	Map();

	sf::RenderWindow *window;
	sf::Sprite *map;

	sf::Image *grassHitbox;

	sf::View *view;
};