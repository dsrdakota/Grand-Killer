#pragma once

#pragma once

// Trailer Part 3

#include "../TrailerStates.hpp"
#include "../../../../../../Manager/Text.hpp"
#include "TaxiTrailer.hpp"
#include "../../../../../../Manager/Time.hpp"

#include <SFML/Audio.hpp>

class Part3 : public TrailerStates
{
public:

	Part3();
	~Part3();

	void play(sf::RenderWindow *window, const sf::Time &time, Music &background, bool &changePart) override;

private:
	
	TaxiTrailer *taxi;

	sf::View *view;

	sf::Sprite *actualTarget, *player, *playerSite, *feet, *head;

	sf::Sound *carSound;

	unsigned *frameOfImagePlayer;

	void frames(sf::RenderWindow *window);
};