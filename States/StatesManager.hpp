#pragma once

#include <SFML/Graphics.hpp>

class GameStates;

class GameStatesManager
{
public:

	GameStatesManager();
	~GameStatesManager();

	void runState();

private:

	enum class States
	{
		Loader,
		Intro,
		mGame
	};

	States actualState;
	std::vector<GameStates*>states;

	void changeState();
};