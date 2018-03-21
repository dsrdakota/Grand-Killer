#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../Game.hpp"

class Painter
{
public:

	Painter() : window(Game::Instance().getWindow()) { }

	inline static Painter& Instance()
	{
		static Painter engine;
		return engine;
	}

	void addToDraw(sf::Drawable *object);
	void addToInterfaceDraw(sf::Drawable *object);

	void run();

private:
	~Painter() {  }

	std::vector<sf::Drawable*> objects;
	std::vector<sf::Drawable*> interface;

	sf::RenderWindow* window;
};