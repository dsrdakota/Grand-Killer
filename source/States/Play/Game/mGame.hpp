#pragma once

#include <SFML/Graphics.hpp>

#include "../../States.hpp"

#include "../../../Engine/Engine.hpp"
#include "../../../Car/Car.hpp"
#include "../../../Map/MapsManager.hpp"
#include "Menu/Menu.hpp"

class mGame : public GameStates
{
public:

	mGame();
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

	state *gameState;

	std::vector<Car*> cars;

	MenuInGame *menu;

	MapsManager *maps;
	
	IObject *player;

	void draw();

	void switchState();

	Time cooldown;
};
