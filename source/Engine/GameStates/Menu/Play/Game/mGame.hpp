#pragma once

#include "../../../../smallerEngine.hpp"
#include "Map.hpp"
#include "../../../../Car/Car.hpp"
#include "../../../../Player/Player.hpp"

#include <SFML/Graphics.hpp>

class mGame : public smallerEngine
{
public:
	~mGame();

	mGame(const mGame &) = delete;
	void operator=(const mGame &) = delete;

	inline static mGame& Instance()
	{
		static mGame game;
		return game;
	}

	void play() override;

	std::vector<Car*> getAllCars();

private:

	mGame();

	std::vector<Car*> *cars;

	Map *map;
	Player *player;
	Car *taxi;
};
