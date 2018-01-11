#pragma once

// Trailer Part 1

#include "../TrailerStates.hpp"
#include "../../../../../../Manager/Time.hpp"

#include <SFML/Audio.hpp>

class Part1 : public TrailerStates
{
public:

	Part1();
	~Part1();

	void play(sf::RenderWindow *window, const sf::Time &time, Music &background, bool &changePart) override;

private:

	sf::Sprite *player, *phone;
	sf::Sound talk, phoneRing;

	void frames(sf::RenderWindow *window);
};