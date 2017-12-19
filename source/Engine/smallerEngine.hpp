#pragma once

#include "../Game.hpp"

class  smallerEngine
{
public:
	inline smallerEngine() : game(Game::Instance()), window(game.getWindow()) {  }

	virtual void play() = 0;

	Game &game;
	sf::RenderWindow *window;
};