#pragma once

#include "../../../../smallerEngine.hpp"
#include "../../../../GamePhysics/Map/Map.hpp"
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

	std::vector<Car*> getAllCars();

private:

	mGame();

	state *gameState;

	std::vector<Car*> cars;

	MenuInGame *menu;

	Map *map;
	Player *player;
	Car *taxi;
	Car *taxi2;

	void draw();

	void switchState();
};
