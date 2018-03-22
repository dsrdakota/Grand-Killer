#include "ObjectBehaviors.hpp"

void ObjectBehaviors::control()
{
	if (car)
		controlCar();
	else
		controlBody();
}

// finding the closest car in player area
// finding path to the door
void ObjectBehaviors::getInCar(Car * car)
{
	this->car = car;

	showCarName();
}

void ObjectBehaviors::getOutOfCar()
{
	this->car = nullptr;

	stateKeyGas = false;
	stateKeyBrake = false;
	stateKeyLeftTurn = false;
	stateKeyRightTurn = false;
}

bool & ObjectBehaviors::getStateKeyGas()
{
	return stateKeyGas;
}

bool & ObjectBehaviors::getStateKeyBrake()
{
	return stateKeyBrake;
}

bool & ObjectBehaviors::getStateKeyLeftTurn()
{
	return stateKeyLeftTurn;
}

bool & ObjectBehaviors::getStateKeyRightTurn()
{
	return stateKeyRightTurn;
}