// Wszelkie prawa zastrze¿one! © 2018 10kw10 
#include "Game.hpp"
#include "Framework/Error.hpp"

int main()
{
	auto &error = Error::Instance();
	error.checkAllFiles();

	if (error.getErrorBool())
		error.showCommunicate();
	else
		Game::Instance().run();

	return 0;
}