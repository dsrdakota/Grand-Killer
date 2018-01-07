#include "Player.hpp"

Player::Player()
{
	wsk = &player;
}

Player::~Player()
{
	delete wsk;
}

float Player::getRotation()
{
	return wsk->getRotation();
}

void Player::move()
{
	wsk->toControl();
	wsk->setCamera();
}

void Player::giveMeYourCar(Car *car)
{
	wsk = car;
}

void Player::changeStates()
{
	wsk = &player;
}

void Player::draw()
{
	wsk->draw();
}
