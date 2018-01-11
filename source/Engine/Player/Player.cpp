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

sf::Vector2f Player::getPosition()
{
	return wsk->getPosition();
}

void Player::move()
{
	wsk->toControl();
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
