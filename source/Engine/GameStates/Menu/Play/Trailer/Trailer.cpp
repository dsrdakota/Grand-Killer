#include "Trailer.hpp"
#include "../../../../../Game.hpp"
#include "../../../../../Framework/Error.hpp"
#include "../../../../../Manager/Texture.hpp"

Trailer::Trailer() : game(Game::Instance()), window(game.getWindow()), actualPart(TrailerStates::statePart::Begin)
{
	Part1 *p1 = nullptr;
	Part2 *p2 = nullptr;
	Part3 *p3 = nullptr;

	wsk = nullptr;
}

Trailer::~Trailer()		
{
	wsk = nullptr;
	delete p1;
	delete p2;
	delete p3;
	delete wsk;

	window->setView(window->getDefaultView());
}

void Trailer::play()
{
	Music background("data/Trailer/Sound/background.wav");

	background.music->setVolume(30);

	background.music->play();

	window->setMouseCursorVisible(false);

	bool isChangePart = true;

	while ( /* do zmiany*/ Game::Instance().getStatus() != Game::status::CleaningUp
		&& actualPart != TrailerStates::statePart::End)
	{
		if (Error::Instance().getErrorBool())
		{
			background.music->stop();
			Error::showCommunicate();
			break;
		}

		game.events();

		if (isChangePart)
			changePart(actualPart, isChangePart);

		if(wsk != nullptr)
			wsk->play(window, trailerTime::getTime(), background,isChangePart);

		trailerTime::getTimetoClock();
	}
}

void Trailer::changePart(TrailerStates::statePart &partNumber, bool &isChangePart)
{
	partNumber = static_cast<TrailerStates::statePart>(static_cast<int>(partNumber) + 1); // next Part
	switch (partNumber)
	{
	case TrailerStates::statePart::First:
		p1 = new Part1;
		wsk = p1;
		break;
	case TrailerStates::statePart::Second:
		p2 = new Part2;
		wsk = p2;
		break;
	case TrailerStates::statePart::Third:
		p3 = new Part3;
		wsk = p3;
		break;
	}
	isChangePart = false;
}