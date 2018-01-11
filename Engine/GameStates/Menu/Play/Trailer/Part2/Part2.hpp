#pragma once

// Trailer Part 2

#include "../../../../../../Game.hpp"
#include "../TrailerStates.hpp"
#include "../../../../../../Manager/Text.hpp"
#include "../../../../../../Manager/Time.hpp"

#include <SFML/Audio.hpp>

class Part2 : public TrailerStates
{
public:

	Part2();
	~Part2();

	void play(sf::RenderWindow *window, const sf::Time &time, Music &background, bool &changePart) override;

private:
	unsigned *characterSize;
	bool *show;
	Text *nick, *present, *gameName;

	sf::Sound showGameName, planeSound;

	sf::Sprite *plane;

	void frames(sf::RenderWindow *window);
};