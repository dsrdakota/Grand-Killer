#include "IObject.hpp"

#include "../Car/Car.hpp"

void IObject::control()
{
	if (car)
		controlCar();
	else
		controlBody();
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
