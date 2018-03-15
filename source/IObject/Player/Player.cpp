#include "Player.hpp"

#include "../../Engine/Engine.hpp"
#include "../../Car/Car.hpp"

Player::Player(const sf::Vector2f &startPos, const float &startRot)
{
	sprite = new sf::Sprite;
	sprite->setPosition(startPos);
	sprite->setRotation(startRot);

	hp = 100;
	armor = 100;
	condition = 100;
}

void Player::controlBody()
{
}

void Player::controlCar()
{
	if (!sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Rodzaj::Break)) && sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Rodzaj::Gas)))
		car->getMovementClass()->gas();
	else if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Rodzaj::Break)))
		car->getMovementClass()->brake();

	else if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Rodzaj::HandBreak)))
		car->getMovementClass()->handBrake();

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Rodzaj::TurnLeft)))
		car->getToTurnClass()->turning(ToTurn::Direction::Left);
	else if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Rodzaj::TurnRight)))
		car->getToTurnClass()->turning(ToTurn::Direction::Right);
}
