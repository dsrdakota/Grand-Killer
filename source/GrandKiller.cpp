#include "Game.hpp"
#include "Framework/Error.hpp"

#include <SFML/System.hpp>

int main()
{
	auto &error = Error::Instance();

	sf::Thread thread(&Error::checkAllFiles,&error);
	thread.launch();

	auto &game = Game::Instance();

	game.run();

	return 0;
}