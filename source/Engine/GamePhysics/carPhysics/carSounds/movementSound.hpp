#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../../../Car/Car.hpp"
#include "../../../../Manager/Time.hpp"

class movementSound
{
public:

	movementSound(Car *car);
	~movementSound();

	void play();

private:

	Car * car;

	Time time;

	bool isSetW;
	bool isSetS;

	sf::Sound *accelerationSound;
	sf::Sound *brakingSound;
	sf::Sound *stopSound;

};