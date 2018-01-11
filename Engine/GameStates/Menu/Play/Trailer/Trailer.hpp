#pragma once

#include "../../../../smallerEngine.hpp"
#include "../../../../../Game.hpp"
#include "../../../../../Manager/Time.hpp"
#include "../../../../../Manager/Music.hpp"

#include "TrailerStates.hpp"

#include "Part1/Part1.hpp"
#include "Part2/Part2.hpp"
#include "Part3/Part3.hpp"

class Trailer : public smallerEngine
{
public:
	Trailer();
	~Trailer();

	void play() override;

	void changePart(TrailerStates::statePart &partNumber, bool &isChangePart);

private:

	Game &game;
	sf::RenderWindow* window;
	TrailerStates *wsk;

	Part1 *p1;
	Part2 *p2;
	Part3 *p3;

	TrailerStates::statePart actualPart;

	friend Game;
};
