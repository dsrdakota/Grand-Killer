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
	if (!sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Break)) && sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Gas)))
		car->getMovementClass()->gas();
	else
		stateKeyGas = false;

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Break)))
		car->getMovementClass()->brake();
	else
		stateKeyBrake = false;

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::HandBreak)))
		car->getMovementClass()->handBrake();

	if(!stateKeyGas && !stateKeyBrake)
		car->getMovementClass()->slack();

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::TurnLeft)))
		car->getToTurnClass()->turning(ToTurn::Direction::Left);
	else
		stateKeyLeftTurn = false;

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::TurnRight)))
		car->getToTurnClass()->turning(ToTurn::Direction::Right);
	else
		stateKeyRightTurn = false;

	car->getToTurnClass()->updatePosition();
}
