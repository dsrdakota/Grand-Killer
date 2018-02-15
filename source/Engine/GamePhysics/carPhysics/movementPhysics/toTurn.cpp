#include "toTurn.hpp"

#include "Slide.hpp"

#include "../../../GameStates/Menu/Play/Game/mGame.hpp"
#include "../collisionPhysics/carCollisionWithCar.hpp"

#define M_PI 3.14159265359f

toTurn::toTurn(Car *car, std::pair<sf::Sprite*, sf::Sprite*>tiresFront, std::pair<sf::Sprite*, sf::Sprite*>tiresBack, const double *speedRotateTire, const double*speedRotateCar)
{
	this->car = car;
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

	if (*actualValueRotateLeftTire)
		rotateCar(static_cast<float>(*actualValueRotateLeftCar), Car::collisionSide::Left, Car::collisionSide::Right, std::make_pair(car->getCollisionHitbox(Car::hitboxPosition::upLeft),car->getCollisionHitbox(Car::hitboxPosition::downLeft)));

	else if (*actualValueRotateRightTire)
		rotateCar(static_cast<float>(-*actualValueRotateRightCar), Car::collisionSide::Right, Car::collisionSide::Left, std::make_pair(car->getCollisionHitbox(Car::hitboxPosition::upRight), car->getCollisionHitbox(Car::hitboxPosition::downRight)));

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

void toTurn::rotateCar(const float & actualValueRotateCar, const Car::collisionSide &sideFirst, const Car::collisionSide &sideSecond, const std::pair<std::vector<sf::CircleShape*>, std::vector<sf::CircleShape*>>&hitboxLeftRight)
{
	float valueRotate = actualValueRotateCar;

	if (car->getSpeed() < 4)
		valueRotate = actualValueRotateCar * static_cast<float>(car->getSpeed()) /4.f;

	if (!car->getStateMoving() && !car->getBoolIsCollision(sideFirst) && !checkCollisionWithOneHitbox(hitboxLeftRight.first, -valueRotate))
	{
		int side = valueRotate > 0 ? 2 : 1; // right : left

		if (car->getOverSteerSide() == side)
			car->rotate(-valueRotate * 0.8);
		else
			car->rotate(-valueRotate);
	}
	else if (car->getStateMoving() == 1 && !car->getBoolIsCollision(sideSecond) && !checkCollisionWithOneHitbox(hitboxLeftRight.second, valueRotate))
		car->rotate(valueRotate);
}

bool toTurn::checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle)
{
	rotateOneHitbox(hitbox, angle);
	bool toReturn = false;
	for (const auto &i : hitbox)
		if (Map::isPointInCollisionArea(getCenterOfHitbox(*i)))
		{
			car->setSpeed(static_cast<float>(car->getSpeed() / 1.03f));
			toReturn = true;
			break;
		}

	const auto &cars = mGame::Instance().getAllCars();

	for (const auto &i : cars)
		if (carCollisionWithCar::checkCollisions(car, i, false) != Car::collisionSide::None)
		{
			car->setSpeed(static_cast<float>(car->getSpeed() / 1.03f));
			toReturn = true;
			break;
		}

	rotateOneHitbox(hitbox, -angle);
	return toReturn;
}

void toTurn::rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle)
{
	for (const auto &i : hitbox)
		i->rotate(angle);
}

sf::Vector2f toTurn::getCenterOfHitbox(const sf::CircleShape & hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
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
