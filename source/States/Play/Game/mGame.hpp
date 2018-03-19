#pragma once

#include "../../States.hpp"
#include "../../../Map/Map.hpp"
#include "../../../Car/Car.hpp"
#include "../../../IObject/Player/Player.hpp"
#include "Menu/Menu.hpp"

#include <SFML/Graphics.hpp>

class mGame : public GameStates
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

	bool play() override;

	std::vector<Car*> &getAllCars();

private:

	mGame();

	state *gameState;

	std::vector<Car*> cars;

	Menu *menu;

	Map *map;
	Player *player;

	void draw();

	void switchState();

	Time cooldown;
	void switchCars(size_t &index);
};
