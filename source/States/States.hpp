#pragma once

#include "../Game.hpp"

class  GameStates
{
public:
	inline GameStates() : game(Game::Instance()), window(game.getWindow()) {  }

	virtual bool play() = 0;

protected:

	Game &game;
	sf::RenderWindow *window;
};