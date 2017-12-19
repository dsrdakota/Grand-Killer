#include "carPhycics.hpp"

#include "../Car/Car.hpp"
#include <iostream>

carPhycics::carPhycics(Car *car)
{
	this->car = car->getShape()->getShape();

	switch (*car->getType())
	{
	case carType::Type::Ambulance:
		break;
	case carType::Type::Audi:
		break;
	case carType::Type::Black_viper:
		break;
	case carType::Type::Car:
		break;
	case carType::Type::Mini_truck:
		break;
	case carType::Type::Mini_van:
		break;
	case carType::Type::Police:
		break;
	case carType::Type::Taxi:

		SPEED_ROTATE_CAR = new double(0.2);
		SPEED_ROTATE_TIRE = new const double(5);

		break;
	case carType::Type::Truck:
		break;
	}

	turnPhycics = new toTurn(car, std::make_pair(car->getTires()->getTires(0), car->getTires()->getTires(1)), std::make_pair(car->getTires()->getTires(2), car->getTires()->getTires(3)),car->getTires()->getPairTireHitboxFront(), SPEED_ROTATE_TIRE,SPEED_ROTATE_CAR);
	movePhycics = new Movement(car);
}

carPhycics::~carPhycics()
{
	delete turnPhycics;
}

void carPhycics::boostSpeed(const sf::Keyboard::Key &key)
{
	movePhycics->gas(key);
}

void carPhycics::reduceSpeed(const sf::Keyboard::Key &key)
{
	movePhycics->brake(key);
}

void carPhycics::handBrake(const sf::Keyboard::Key & key)
{
	movePhycics->handBrake(key);
}

void carPhycics::turn(const toTurn::Direction & direction)
{
	turnPhycics->turning(direction);
}

void carPhycics::updatePosition()
{
	turnPhycics->updatePosition();
	movePhycics->updatePosition();
}

void carPhycics::move(const sf::Vector2f &offset)
{
	
}

void carPhycics::draw()
{
	
}
