#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Game.hpp"

class renderSprites
{
public:

	renderSprites() : window(Game::Instance().getWindow()) { }

	inline static renderSprites& Instance()
	{
		static renderSprites engine;
		return engine;
	}

	void addToRender(sf::Drawable *object);

	void run();

private:
	~renderSprites() {  }

	inline void clearVector() { sprites.clear(); }

	std::vector<sf::Drawable*> sprites;

	sf::RenderWindow* window;
};