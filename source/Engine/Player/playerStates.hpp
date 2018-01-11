#pragma once

#include "../../Game.hpp"
#include "../GamePhysics/Map/Map.hpp"
#include "../../Manager/Text.hpp"

class playerStates
{
public:
	
	playerStates() : window(Game::Instance().getWindow()), view(&Map::Instance()){}

	enum class Vechicle
	{
		onFoot,
		Car
	};

	virtual void toControl() = 0;
	virtual float getRotation() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual void draw() = 0;

protected:
	sf::RenderWindow *window;
	Map *view;
};