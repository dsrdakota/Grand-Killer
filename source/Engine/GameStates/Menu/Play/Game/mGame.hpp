#pragma once

#include "../../../../smallerEngine.hpp"
#include "../../../../Map/Map.hpp"
#include "../../../../Car/Car.hpp"
#include "../../../../Player/Player.hpp"
#include "MenuInGame/MenuInGame.hpp"

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

	enum class state
	{
		MainGame,
		Menu,
		Map
	};

	void play() override;

	std::vector<Car*> &getAllCars();

private:

	mGame();

	state *gameState;

	std::vector<Car*> cars;

	MenuInGame *menu;

	Map *map;
	Player *player;

	void draw();

	void switchState();

	Time cooldown;
	void switchCars(size_t &index);
};
