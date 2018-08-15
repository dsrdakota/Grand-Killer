#include "toTurn.hpp"

#include "../../States/Play/Game/mGame.hpp"

#include "../Car.hpp"

#include "../../Map/Map.hpp"

#include <fstream>

#define M_PI 3.14159265359f

ToTurn::ToTurn(Car *car)
{
	this->car = car;

	SPEED_ROTATE_CAR = new double(CarConfig::getValue(car->getName(), "SPEED_ROTATE_CAR"));
	SPEED_ROTATE_TIRE = new double(CarConfig::getValue(car->getName(), "SPEED_ROTATE_TIRE"));

	actualValueRotateLeftCar = new double(0);
	actualValueRotateRightCar = new double(0);
	actualValueRotateLeftTire = new double(0);
	actualValueRotateRightTire = new double(0);
	MAX_ROTATE_TIRE = new const double(50);
	MAX_ROTATE_CAR = new const double(2);

	drivingStatus = new Status(Status::Straight);
	slide = new Slide(car);
	
	this->tiresFront = std::make_pair(car->getTireClass()->getTires(0), car->getTireClass()->getTires(1));
	this->tiresBack = std::make_pair(car->getTireClass()->getTires(2), car->getTireClass()->getTires(3));
}

ToTurn::~ToTurn()
{
	delete SPEED_ROTATE_TIRE;
	delete SPEED_ROTATE_CAR;

	delete MAX_ROTATE_CAR;
	delete MAX_ROTATE_TIRE;

	delete actualValueRotateLeftCar;
	delete actualValueRotateRightCar;

	delete actualValueRotateLeftTire;
	delete actualValueRotateRightTire;

	delete drivingStatus;
}

Slide * ToTurn::getSlidePhycics()
{
	return slide;
}

void ToTurn::turning(const Direction & direction)
{
	if (direction == Direction::Left)
		car->getDriver()->getBehaviors()->getStateKeyLeftTurn() = true;
	else
		car->getDriver()->getBehaviors()->getStateKeyRightTurn() = true;

	if (car->getDriver()->getBehaviors()->getStateKeyLeftTurn() && *actualValueRotateRightTire <= 0)
	{
		turn(tiresFront.first, tiresFront.second, actualValueRotateLeftTire, -*SPEED_ROTATE_TIRE, actualValueRotateLeftCar, SPEED_ROTATE_CAR);
		resetValue(2, actualValueRotateRightTire, actualValueRotateRightCar);
	}

	else if (car->getDriver()->getBehaviors()->getStateKeyRightTurn() && *actualValueRotateLeftTire <= 0)
	{
		turn(tiresFront.second, tiresFront.first, actualValueRotateRightTire, *SPEED_ROTATE_TIRE, actualValueRotateRightCar, SPEED_ROTATE_CAR);
		resetValue(2, actualValueRotateLeftTire, actualValueRotateLeftCar);
	}
}

void ToTurn::updatePosition()
{
	if (car->getDriver())
	{
		if (!car->getDriver()->getBehaviors()->getStateKeyLeftTurn() && *actualValueRotateLeftTire > 0)
		{
			straight(tiresFront.first, tiresFront.second, actualValueRotateLeftTire, *SPEED_ROTATE_TIRE, actualValueRotateLeftCar, SPEED_ROTATE_CAR);
			resetValue(2, actualValueRotateRightTire, actualValueRotateRightCar);
		}

		else if (!car->getDriver()->getBehaviors()->getStateKeyRightTurn() && *actualValueRotateRightTire > 0)
		{
			straight(tiresFront.second, tiresFront.first, actualValueRotateRightTire, -*SPEED_ROTATE_TIRE, actualValueRotateRightCar, SPEED_ROTATE_CAR);
			resetValue(2, actualValueRotateLeftTire, actualValueRotateLeftCar);
		}
		else if (!car->getDriver()->getBehaviors()->getStateKeyLeftTurn() && !car->getDriver()->getBehaviors()->getStateKeyRightTurn())
			resetValue(4, actualValueRotateLeftCar, actualValueRotateLeftTire, actualValueRotateRightCar, actualValueRotateRightTire);
	}
	else
	{
		if (*actualValueRotateLeftTire > 0)
		{
			straight(tiresFront.first, tiresFront.second, actualValueRotateLeftTire, *SPEED_ROTATE_TIRE, actualValueRotateLeftCar, SPEED_ROTATE_CAR);
			resetValue(2, actualValueRotateRightTire, actualValueRotateRightCar);
		}

		else if (*actualValueRotateRightTire > 0)
		{
			straight(tiresFront.second, tiresFront.first, actualValueRotateRightTire, -*SPEED_ROTATE_TIRE, actualValueRotateRightCar, SPEED_ROTATE_CAR);
			resetValue(2, actualValueRotateLeftTire, actualValueRotateLeftCar);
		}
	}

	if (*actualValueRotateLeftCar > 0)
		*drivingStatus = Status::TurningLeft;
	else if (*actualValueRotateRightCar > 0)
		*drivingStatus = Status::TurningRight;
	else
		*drivingStatus = Status::Straight;

	if (*actualValueRotateLeftTire)
		rotateCar(static_cast<float>(*actualValueRotateLeftCar));

	else if (*actualValueRotateRightTire)
		rotateCar(static_cast<float>(-*actualValueRotateRightCar));

	slide->setOverSteer(static_cast<int>(*drivingStatus));
}

void ToTurn::turn(sf::RectangleShape *tire, sf::RectangleShape *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar)
{
	if (*actualValueRotateTire < *MAX_ROTATE_TIRE)
	{
		tire->rotate(static_cast<float>(angleTire));

		counterTire->setRotation(tire->getRotation());

		addValue(*actualValueRotateTire, fabs(angleTire), *MAX_ROTATE_TIRE);
		addValue(*actualValueRotateCar, *angleCar, *MAX_ROTATE_CAR);
	}
}

void ToTurn::straight(sf::RectangleShape *tire, sf::RectangleShape *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar)
{
	if (*actualValueRotateTire > 0)
	{
		tire->rotate(static_cast<float>(angleTire));

		counterTire->setRotation(tire->getRotation());

		reduceValue(*actualValueRotateTire, fabs(angleTire), 0);
		reduceValue(*actualValueRotateCar, *angleCar, 0);
	}
}

void ToTurn::rotateCar(const float & actualValueRotateCar)
{
	float valueRotate = actualValueRotateCar;

	if (car->getSpeed() < 4)
		valueRotate = actualValueRotateCar * static_cast<float>(car->getSpeed()) / 4.f;

	if (car->getStateMoving() != Moveable::StateMoving::Stop)
	{
		int side = valueRotate > 0 ? 2 : 1; // right : left

		if (car->getToTurnClass()->getSlidePhycics()->getOverSteerSide() == side)
			car->rotate(-valueRotate * 0.8f);
		else
			car->rotate(-valueRotate);
	}
	else if (car->getStateMoving() == Moveable::StateMoving::Back)
		car->rotate(valueRotate);
}

void ToTurn::addValue(double & value, const double & addValue, const double & max)
{
	if (value + addValue <= max)
		value += addValue;
	else
		value = max;
}

void ToTurn::reduceValue(double & value, const double & reduceValue, const double & min)
{
	if (value - reduceValue > min)
		value -= reduceValue;
	else
		value = min;
}

void ToTurn::resetValue(const unsigned value, ...)
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