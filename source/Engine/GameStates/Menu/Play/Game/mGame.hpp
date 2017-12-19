#pragma once

#include "../../../../smallerEngine.hpp"
#include "Map.hpp"
#include "../../../../Car/Car.hpp"
#include "../../../../Player/Player.hpp"

#include <SFML/Graphics.hpp>

class mGame : public smallerEngine
{
public:

	mGame();
	~mGame();

	void play() override;

private:

	Map *map;
	Player *player;
	Car *taxi;
};
