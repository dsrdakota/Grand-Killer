#include "IObject.hpp"

#include "../Car/Car.hpp"

Car* IObject::getCar()
{
	return car;
}

void IObject::getInCar(Car * car)
{
	car->setDriver(this);
	this->car = car;

	getBehaviors()->getInCar(car);
}

void IObject::getOutOfCar()
{
	car->setDriver(nullptr);
	this->car = nullptr;

	getBehaviors()->getOutOfCar();
}

const sf::Vector2f & IObject::getPosition()
{
	if (car != nullptr)
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
