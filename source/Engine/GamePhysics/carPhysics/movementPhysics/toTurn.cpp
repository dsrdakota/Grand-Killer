#include "toTurn.hpp"

#include "Slide.hpp"
#include "../collisionPhysics/Collision.hpp"

#define M_PI 3.14159265359f

toTurn::toTurn(Car *car, std::pair<sf::Sprite*, sf::Sprite*>tiresFront, std::pair<sf::Sprite*, sf::Sprite*>tiresBack, const double *speedRotateTire, const double*speedRotateCar)
{
	this->car = car;
	this->carShape = car->getShape()->getShape();
	SPEED_ROTATE_TIRE = speedRotateTire;
	SPEED_ROTATE_CAR = speedRotateCar;
	actualValueRotateLeftCar = new double(0);
	actualValueRotateRightCar = new double(0);
	actualValueRotateLeftTire = new double(0);
	actualValueRotateRightTire = new double(0);
	MAX_ROTATE_TIRE = new const double(50);
	MAX_ROTATE_CAR = new double(2);

	drivingStatus = new Status(Status::Straight);
	slide = new Slide(car);

	keyToLeftTurn = new keyStatus(keyStatus::Released);
	keyToRightTurn = new keyStatus(keyStatus::Released);
	
	this->tiresFront = tiresFront;
	this->tiresBack = tiresBack;
}

toTurn::~toTurn()
{
	delete SPEED_ROTATE_TIRE;
	delete SPEED_ROTATE_CAR;
	delete MAX_ROTATE_CAR;
	delete MAX_ROTATE_TIRE;
	delete keyToLeftTurn;
	delete keyToRightTurn;

	delete actualValueRotateLeftCar;
	delete actualValueRotateRightCar;

	delete actualValueRotateLeftTire;
	delete actualValueRotateRightTire;

	delete drivingStatus;
}

toTurn::keyStatus* toTurn::getStatusKeyToTurn(const Direction & direction)
{
	if (direction == Direction::Left)
		return keyToLeftTurn;
	return keyToRightTurn;
}

const double * toTurn::getOverSteerValue()
{
	return slide->getOverSteer();
}

Slide * toTurn::getSlidePhycics()
{
	return slide;
}

bool toTurn::isSlide()
{
	return slide->getSlideBool();
}

void toTurn::breakSlide()
{
	slide->breakSlide();
}

void toTurn::turning(const Direction & direction)
{
	if (direction == Direction::Left)
		*keyToLeftTurn = keyStatus::Pressed;
	else
		*keyToRightTurn = keyStatus::Pressed;

	if (*keyToLeftTurn == keyStatus::Pressed && *actualValueRotateRightTire <= 0)
	{
		turn(tiresFront.first, tiresFront.second, actualValueRotateLeftTire, -*SPEED_ROTATE_TIRE, actualValueRotateLeftCar, SPEED_ROTATE_CAR);
		resetValue(2, actualValueRotateRightTire, actualValueRotateRightCar);
	}

	else if (*keyToRightTurn == keyStatus::Pressed && *actualValueRotateLeftTire <= 0)
	{
		turn(tiresFront.second, tiresFront.first, actualValueRotateRightTire, *SPEED_ROTATE_TIRE, actualValueRotateRightCar, SPEED_ROTATE_CAR);
		resetValue(2, actualValueRotateLeftTire, actualValueRotateLeftCar);
	}
}

void toTurn::updatePosition()
{
	if (*keyToLeftTurn == keyStatus::Released && *actualValueRotateLeftTire > 0)
	{
		straight(tiresFront.first, tiresFront.second, actualValueRotateLeftTire, *SPEED_ROTATE_TIRE, actualValueRotateLeftCar, SPEED_ROTATE_CAR);
		resetValue(2, actualValueRotateRightTire, actualValueRotateRightCar);
	}

	else if (*keyToRightTurn == keyStatus::Released && *actualValueRotateRightTire > 0)
	{
		straight(tiresFront.second, tiresFront.first, actualValueRotateRightTire, -*SPEED_ROTATE_TIRE, actualValueRotateRightCar, SPEED_ROTATE_CAR);
		resetValue(2, actualValueRotateLeftTire, actualValueRotateLeftCar);
	}
	else if(*keyToLeftTurn == keyStatus::Released && *keyToRightTurn == keyStatus::Released)
		resetValue(4, actualValueRotateLeftCar, actualValueRotateLeftTire, actualValueRotateRightCar, actualValueRotateRightTire);

	if (*actualValueRotateLeftCar > 0)
		*drivingStatus = Status::TurningLeft;
	else if (*actualValueRotateRightCar > 0)
		*drivingStatus = Status::TurningRight;
	else
		*drivingStatus = Status::Straight;

	if (*actualValueRotateLeftTire && car->getSpeed() > 0.65)
		rotateCar(static_cast<float>(*actualValueRotateLeftCar), Car::collisionSide::Left, Car::collisionSide::Right);

	else if (*actualValueRotateRightTire && car->getSpeed() > 0.65)
		rotateCar(static_cast<float>(-*actualValueRotateRightCar), Car::collisionSide::Right, Car::collisionSide::Left);

	slide->setOverSteer(static_cast<int>(*drivingStatus));
}

void toTurn::turn(sf::Sprite *tire, sf::Sprite *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar)
{
	if (*actualValueRotateTire < *MAX_ROTATE_TIRE)
	{
		tire->rotate(static_cast<float>(angleTire));

		counterTire->setRotation(tire->getRotation());

		addValue(*actualValueRotateTire, fabs(angleTire), *MAX_ROTATE_TIRE);
		addValue(*actualValueRotateCar, *angleCar, *MAX_ROTATE_CAR);
	}
}

void toTurn::straight(sf::Sprite *tire, sf::Sprite *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar)
{
	if (*actualValueRotateTire > 0)
	{
		tire->rotate(static_cast<float>(angleTire));

		counterTire->setRotation(tire->getRotation());

		reduceValue(*actualValueRotateTire, fabs(angleTire), 0);
		reduceValue(*actualValueRotateCar, *angleCar, 0);
	}
}

void toTurn::rotateCar(const float & actualValueRotateCar, const Car::collisionSide &sideFirst, const Car::collisionSide &sideSecond)
{
	if (!car->getStateMoving() && !car->getBoolIsCollision(sideFirst))
	{
		if (car->getOverSteerSide() == 2)
			car->rotate(-actualValueRotateCar * 0.8);
		else
			car->rotate(-actualValueRotateCar);
	}
	else if (car->getStateMoving() == 1 && !car->getBoolIsCollision(sideSecond))
		car->rotate(actualValueRotateCar);
}

void toTurn::addValue(double & value, const double & addValue, const double & max)
{
	if (value + addValue <= max)
		value += addValue;
	else
		value = max;
}

void toTurn::reduceValue(double & value, const double & reduceValue, const double & min)
{
	if (value - reduceValue > min)
		value -= reduceValue;
	else
		value = min;
}

void toTurn::resetValue(const unsigned value, ...)
{
	va_list vl;
	va_start(vl, value);
	double *val;
	for (unsigned i = 0;i < value;++i)
	{
		val = va_arg(vl, double*);
		*val = 0;
	}
	va_end(vl);
}