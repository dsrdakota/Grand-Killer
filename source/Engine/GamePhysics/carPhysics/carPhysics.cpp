#include "carPhysics.hpp"

#include "../../Car/Car.hpp"

#include <iostream>

carPhysics::carPhysics(Car *car)
{
	switch (*car->getType())
	{
	case carType::Type::Ambulance:

		SPEED_ROTATE_CAR = new double(0.15);
		SPEED_ROTATE_TIRE = new const double(3);

		break;
	case carType::Type::Audi:

		SPEED_ROTATE_CAR = new double(0.2);
		SPEED_ROTATE_TIRE = new const double(5);

		break;
	case carType::Type::Black_viper:

		SPEED_ROTATE_CAR = new double(0.3);
		SPEED_ROTATE_TIRE = new const double(5);

		break;
	case carType::Type::Car:

		SPEED_ROTATE_CAR = new double(0.25);
		SPEED_ROTATE_TIRE = new const double(5);

		break;
	case carType::Type::Mini_truck:

		SPEED_ROTATE_CAR = new double(0.18);
		SPEED_ROTATE_TIRE = new const double(4);

		break;
	case carType::Type::Police:

		SPEED_ROTATE_CAR = new double(0.23);
		SPEED_ROTATE_TIRE = new const double(5);

		break;
	case carType::Type::Taxi:

		SPEED_ROTATE_CAR = new double(0.2);
		SPEED_ROTATE_TIRE = new const double(5);

		break;
	}

	turnPhysics = new toTurn(car, std::make_pair(car->getTires()->getTires(0), car->getTires()->getTires(1)), std::make_pair(car->getTires()->getTires(2), car->getTires()->getTires(3)), SPEED_ROTATE_TIRE, SPEED_ROTATE_CAR);
	movePhysics = new Movement(car);
	collisionHitboxes = new carCollisionHitbox(car);
}

carPhysics::~carPhysics()
{
	delete turnPhysics;
	delete movePhysics;
	delete collisionHitboxes;
}

void carPhysics::boostSpeed(const sf::Keyboard::Key &key)
{
	movePhysics->gas(key);
}

void carPhysics::reduceSpeed(const sf::Keyboard::Key &key)
{
	movePhysics->brake(key);
}

void carPhysics::handBrake(const sf::Keyboard::Key & key)
{
	movePhysics->handBrake(key);
}

void carPhysics::turn(const toTurn::Direction & direction)
{
	turnPhysics->turning(direction);
}

void carPhysics::updatePosition()
{
	turnPhysics->updatePosition();
	movePhysics->updatePosition();
	collisionHitboxes->update();
}

void carPhysics::draw()
{
	collisionHitboxes->draw();
}
