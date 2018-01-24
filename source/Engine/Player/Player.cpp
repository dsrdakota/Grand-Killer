#include "Player.hpp"

Player::Player()
{
	wsk = &player;
	state = new playerState(playerState::Walk);
}

Player::~Player()
{
	delete wsk;
}

float Player::getRotation()
{
	return wsk->getRotation();
}

sf::Vector2f Player::getPosition()
{
	return wsk->getPosition();
}

Player::playerState Player::getState()
{
	return *state;
}

void Player::move()
{
	wsk->toControl();
}

void Player::giveMeYourCar(Car *car)
{
	wsk = car;
	*state = playerState::Vehicle;
}

void Player::changeStates()
{
	wsk = &player;
	*state = playerState::Walk;
}

void Player::draw()
{
	wsk->draw();
}
