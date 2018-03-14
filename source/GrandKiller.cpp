// Wszelkie prawa zastrze¿one! © 2018 10kw10 

#include "Game.hpp"
#include "Engine/Engine.hpp"

int main()
{
	Engine::Instance().init();

	Game::Instance().run();

	Engine::Instance().shutDown();

	return 0;
}