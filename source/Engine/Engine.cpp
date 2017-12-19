#include "Engine.hpp"
#include "../Manager/Time.hpp"
Engine::Engine() : game(Game::Instance())
{
	window = game.getWindow();
	state = Engine::States::Intro;
	wsk = &intro;
}

Engine::~Engine()
{
	
}
 
void Engine::nextPartGame()
{
	Engine &engine = Engine::Instance();
	engine.state = static_cast<States>(static_cast<int>(engine.state) + 1);

	TimeManager::clearVector();

	switch (Engine::Instance().state)
	{
	case Engine::States::Intro:
		engine.wsk = &engine.intro;
		break;
	case Engine::States::Menu:
		engine.wsk = &engine.menu;
		break;
	}
}

