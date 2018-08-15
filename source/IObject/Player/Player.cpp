#include "Player.hpp"

Player::Player(const sf::Vector2f &startPos, const float &startRot)
{
	sprite = new sf::Sprite;
	sprite->setPosition(startPos);
	sprite->setRotation(startRot);

	hp = 100;
	armor = 100;
	condition = 100;

	car = nullptr;

	behaviors = new PlayerBehaviors;
}

Player::~Player()
{
	delete behaviors;
}

PlayerBehaviors * Player::getBehaviors()
{
	return behaviors;
}
