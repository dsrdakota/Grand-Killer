#include "StatesManager.hpp"

#include "States.hpp"
#include "Loading/Loader.hpp"
#include "Intro/Intro.hpp"
#include "Play/Game/mGame.hpp"

GameStatesManager::GameStatesManager()
{
	states.push_back(new Loader());

	actualState = States::Loader;
}

GameStatesManager::~GameStatesManager()
{
	for (const auto &i : states)
		delete i;
}

void GameStatesManager::runState()
{
	while (Game::Instance().getStatus() != Game::status::CleaningUp && actualState <= States::mGame && states[0]->play())
		changeState();
}

void GameStatesManager::changeState()
{
	actualState = static_cast<States>(static_cast<int>(actualState)+1);

	switch (actualState)
	{
	case States::Intro:
		delete states[0];
		states.pop_back();
		states.push_back(new Intro());
		break;
	case States::mGame:
		delete states[0];
		states.pop_back();
		states.push_back(&mGame::Instance());
		break;
	}
}