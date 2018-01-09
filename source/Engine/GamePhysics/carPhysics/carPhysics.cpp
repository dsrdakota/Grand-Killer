#include "carPhysics.hpp"

#include "../../Car/Car.hpp"

carPhysics::carPhysics(Car *car)
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

	turnPhysics = new toTurn(car, std::make_pair(car->getTires()->getTires(0), car->getTires()->getTires(1)), std::make_pair(car->getTires()->getTires(2), car->getTires()->getTires(3)), SPEED_ROTATE_TIRE,SPEED_ROTATE_CAR);
	movePhysics = new Movement(car);
	collisionHitboxes = new carCollisionHitbox(car);
	dentHitboxes = new carDentHitbox(car);
}

carPhysics::~carPhysics()
{
	delete turnPhysics;
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
}

void carPhysics::move(const sf::Vector2f &offset)
{
	
}

void carPhysics::draw()
{
	
}
