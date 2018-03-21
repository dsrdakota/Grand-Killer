#include "IObject.hpp"

#include "../Car/Car.hpp"

void IObject::control()
{
	if (car)
		controlCar();
	else
		controlBody();
}

Car* IObject::getCar()
{
	return car;
}

// finding the closest car in player area
// finding path to the door
void IObject::getInCar(Car * car)
{
	car->setDriver(this);
	this->car = car;
}

void IObject::getOutOfCar()
{
	car->setDriver(nullptr);
	this->car = nullptr;

	stateKeyGas = false;
	stateKeyBrake = false;
	stateKeyLeftTurn = false;
	stateKeyRightTurn = false;
}

const sf::Vector2f & IObject::getPosition()
{
	if (car)
		return car->getSprite()->getPosition();
	else
		return sprite->getPosition();
}

const float IObject::getRotation()
{
	if (car)
		return car->getSprite()->getRotation();
	else
		return sprite->getRotation();
}

void IObject::setHP(const int & hp)
{
	if (hp < 0)
		this->hp = 0;
	else if (hp <= 100)
		this->hp = hp;
}

const int & IObject::getHP() const
{
	return hp;
}

bool & IObject::getStateKeyGas()
{
	return stateKeyGas;
}

bool & IObject::getStateKeyBrake()
{
	return stateKeyBrake;
}

bool & IObject::getStateKeyLeftTurn()
{
	return stateKeyLeftTurn;
}

bool & IObject::getStateKeyRightTurn()
{
	return stateKeyRightTurn;
}
