#pragma once

#include "playerStates.hpp"
#include "../Car/Car.hpp"
#include "../GamePhysics/playerPhysics/playerMechanics.hpp"

class Player
{
public:

	enum class playerState
	{
		Walk,
		Vehicle
	};

	Player(const Player &) = delete;
	void operator=(const Player &) = delete;

	inline static Player& Instance()
	{
		static Player player;
		return player;
	}

	float getRotation();
	sf::Vector2f getPosition();

	playerState getState();

	void move();
	void giveMeYourCar(Car *car); // if you drive a car
	void changeStates(); // if you walk ( get out of car )
	void draw();

private:
	Player();

	playerStates *wsk;
	playerMechanics player;

	playerState *state;

protected:

	~Player();
};