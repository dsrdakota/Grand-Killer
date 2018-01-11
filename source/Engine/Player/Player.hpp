#pragma once

#include "playerStates.hpp"
#include "../Car/Car.hpp"
#include "../GamePhysics/playerPhysics/playerMechanics.hpp"

class Player
{
public:

	Player(const Player &) = delete;
	void operator=(const Player &) = delete;

	inline static Player& Instance()
	{
		static Player player;
		return player;
	}

	float getRotation();
	sf::Vector2f getPosition();

	void move();
	void giveMeYourCar(Car *car); // if you drive a car
	void changeStates(); // if you walk ( get out of car )
	void draw();

private:
	Player();

	playerStates *wsk;
	playerMechanics player;

protected:

	~Player();
};