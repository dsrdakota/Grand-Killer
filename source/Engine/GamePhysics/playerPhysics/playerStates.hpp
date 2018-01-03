#pragma once

#include "../../Game.hpp"
#include "../GameStates/Menu/Play/Game/Map.hpp"
#include "../../Manager/Text.hpp"

class playerStates
{
public:
	
	playerStates() : window(Game::Instance().getWindow()), view(&Map::Instance())
	{
		;
	}

	enum class Vechicle
	{
		onFoot,
		Car
	};

	virtual void toControl() = 0;
	virtual void setCamera() = 0;
	virtual void draw() = 0;

protected:
	sf::RenderWindow *window;
	Map *view;
};