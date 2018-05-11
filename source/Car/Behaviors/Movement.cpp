#include "Movement.hpp"

#include "../../States/Play/Game/mGame.hpp"

#include "../../Physics/Collision/carWithWall.hpp"
#include "../../Physics/Collision/carWithCar.hpp"

#include "../../Map/Map.hpp"

#include "../Car.hpp"
#include <iostream>

#define PI 3.14159265359f

Movement::Movement(Car *car) : car(car)
{
	speedf = new double(0);
	speedb = new double(0);

	movingState = new stateMoving(stateMoving::stop);

	MAX_SPEED = new double(CarConfig::getValue(car->getName(), "MAX_SPEED"));
	acceleration = new double(CarConfig::getValue(car->getName(), "acceleration"));
	breakingForce = new double(CarConfig::getValue(car->getName(), "breakingForce"));
	drive = static_cast<TypeOfDrive>(static_cast<int>(CarConfig::getValue(car->getName(), "typeOfDrive")));

	if (drive != TypeOfDrive::Back)
		tiresDrive = std::make_pair(car->getTireClass()->getTiresPos(0), car->getTireClass()->getTiresPos(1));
	else
		tiresDrive = std::make_pair(car->getTireClass()->getTiresPos(2), car->getTireClass()->getTiresPos(3));
}

Movement::~Movement()
{
	delete speedf;
	delete speedb;
	delete acceleration;
	delete breakingForce;
	delete MAX_SPEED;

	delete movingState;
}

const double * Movement::getSpeed()
{
	double *speed = new double(0);
	if (*speedf && !*speedb)
		return speedf;
	else if (*speedb && !*speedf)
		return speedb;
	return speed;
}

void Movement::setSpeed(const float & speed)
{
	if (speed > 0 && *movingState != stateMoving::stop)
	{
		switch (*movingState)
		{
		case stateMoving::front:

			if (speed < *MAX_SPEED)
				*speedf = speed;

			break;
		case stateMoving::back:

			if (speed < *MAX_SPEED / 2)
				*speedb = speed;

			break;
		}
	}
	else if (speed <= 0)
	{
		*speedf = 0;
		*speedb = 0;
	}
}

const double * Movement::getMaxSpeed()
{
	return MAX_SPEED;
}

void Movement::setCollidSide(const Hitbox::collisionSide & side)
{
	collideSide = side;
}

Hitbox::collisionSide Movement::getCollidSide()
{
	return collideSide;
}

void Movement::updatePosition()
{
	setStateMoving();
	move();
}

void Movement::gas()
{
	if (!car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Front))
	{
		if (!car->getToTurnClass()->getSlidePhycics()->getSlideBool() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			acceleratingFunction(speedf, speedb, *MAX_SPEED, car->getDriver()->getBehaviors()->getStateKeyGas());
		else
			breakingFunction(speedf, 0.1, 5);
	}
	else
		car->getDriver()->getBehaviors()->getStateKeyGas() = false;
}

void Movement::brake()
{
	if (!car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Back))
	{
		if (*speedf <= 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			acceleratingFunction(speedb, speedf, *MAX_SPEED / 2, car->getDriver()->getBehaviors()->getStateKeyGas());
		else
		{
			if (!Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*tiresDrive.first)) ||
				!Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*tiresDrive.second)))
				breakingFunction(speedf, *breakingForce, 0);
			else
				breakingFunction(speedf, *breakingForce / 3, 0); // grass
		}
	}
	else
		car->getDriver()->getBehaviors()->getStateKeyBrake() = false;
}

void Movement::slack()
{
	if (!car->getToTurnClass()->getSlidePhycics()->getSlideBool())
	{
		if (*speedf)
			breakingFunction(speedf);
		else if (*speedb)
			breakingFunction(speedb);
	}
	else
	{
		if (*speedf)
			breakingFunction(speedf, 0.18);
		else if (*speedb)
			breakingFunction(speedb, 0.1);
	}
}

void Movement::handBrake()
{		
	if (!Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*tiresDrive.first)) ||
		!Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*tiresDrive.second)))
		breakingFunction(speedf, 0.18, 0); // asphalt
	else
		breakingFunction(speedf, 0.1, 0); // grass
}

void Movement::setStateMoving()
{
	if (*speedf > 0 && *speedb <= 0)
		*movingState = stateMoving::front;
	else if (*speedb > 0)
		*movingState = stateMoving::back;
	else
		*movingState = stateMoving::stop;
}

void Movement::move()
{
	sf::Vector2f v(0, 0);
	sf::Vector2f w = getMovementVector(car->getSprite()->getRotation() - static_cast<float>(*car->getToTurnClass()->getSlidePhycics()->getOverSteer()));

	double *SPEED = nullptr;
	switch (*movingState)
	{
	case stateMoving::stop:
	case stateMoving::front:
		SPEED = speedf;
		break;
	case stateMoving::back:
		SPEED = speedb;
		w = -w;
		break;
	}

	auto &allCars = mGame::Instance().getAllCars();
	bool breakLoop = false;
	rotateAble = true;
	moveAble = true;

	// rotate crash
	Hitbox::collisionSide rotateFirstCheckingSide = Hitbox::collisionSide::None;
	Hitbox::collisionSide rotateSecondCheckingSide = Hitbox::collisionSide::None;

	// move crash
	Hitbox::collisionSide moveFirstCheckingSide = Hitbox::collisionSide::None;
	Hitbox::collisionSide moveSecondCheckingSide = Hitbox::collisionSide::None;
	Hitbox::collisionSide moveThirdCheckingSide = Hitbox::collisionSide::None;

	if (powerOfCrashRotate.second > 0) // right rotate
	{
		rotateFirstCheckingSide = Hitbox::collisionSide::RightUp;
		rotateSecondCheckingSide = Hitbox::collisionSide::LeftDown;
	}
	else if (powerOfCrashRotate.second < 0) // left rotate
	{
		rotateFirstCheckingSide = Hitbox::collisionSide::LeftUp;
		rotateSecondCheckingSide = Hitbox::collisionSide::RightDown;
	}

	if (collideSide == Hitbox::collisionSide::Front)
	{
		moveFirstCheckingSide = Hitbox::collisionSide::LeftDown;
		moveSecondCheckingSide = Hitbox::collisionSide::Back;
		moveThirdCheckingSide = Hitbox::collisionSide::RightDown;
	}
	else if (collideSide == Hitbox::collisionSide::Back)
	{
		moveFirstCheckingSide = Hitbox::collisionSide::LeftUp;
		moveSecondCheckingSide = Hitbox::collisionSide::Front;
		moveThirdCheckingSide = Hitbox::collisionSide::RightUp;
	}
	else if (collideSide == Hitbox::collisionSide::Left)
	{
		moveFirstCheckingSide = Hitbox::collisionSide::LeftUp;
		moveSecondCheckingSide = Hitbox::collisionSide::Left;
		moveThirdCheckingSide = Hitbox::collisionSide::LeftDown;
	}
	else if (collideSide == Hitbox::collisionSide::Right)
	{
		moveFirstCheckingSide = Hitbox::collisionSide::RightUp;
		moveSecondCheckingSide = Hitbox::collisionSide::Right;
		moveThirdCheckingSide = Hitbox::collisionSide::RightDown;
	}

	// some car simulation like in Box2d ;d

	const float simulationStep = 0.75f;

	for (float i = 1;i <= 4;i += simulationStep)
	{
		v = w * static_cast<float>(*SPEED) / 4.f * simulationStep;
		car->getHitboxClass()->moveHitboxes(v);

		auto resultWithWall = carWithWall::checkCollisions(car, false);

		if (resultWithWall != Hitbox::collisionSide::None)
			powerOfCrashMove = std::make_pair(sf::Vector2f(0, 0), 0.f);

		if (powerOfCrashRotate.second != 0)
		{
			if (resultWithWall == rotateFirstCheckingSide ||
				resultWithWall == rotateSecondCheckingSide)
				rotateAble = false;
		}

		for (const auto &j : allCars)
		{
			auto resultWithCars = carWithCar::checkCollisions(car, j);
			if (resultWithCars != Hitbox::collisionSide::None)
			{
				/*if (resultWithCars == Hitbox::collisionSide::Front &&
					*movingState == stateMoving::front)
					breakLoop = true;

				else if (resultWithCars == Hitbox::collisionSide::Back &&
					*movingState == stateMoving::back)
					breakLoop = true;*/

				if (resultWithCars == moveFirstCheckingSide ||
					resultWithCars == moveSecondCheckingSide ||
					resultWithCars == moveThirdCheckingSide)
				{
					powerOfCrashMove = std::make_pair(sf::Vector2f(0, 0), 0.f);
					moveAble = false;
				}

				if (powerOfCrashRotate.second != 0 && rotateAble)
				{
					if (resultWithCars == rotateFirstCheckingSide ||
						resultWithCars == rotateSecondCheckingSide)
						rotateAble = false;
				}
			}
		}

		if (breakLoop)
			break;

		car->move(v);

		if (rotateAble && fabs(powerOfCrashRotate.second) > fabs(powerOfCrashRotate.first))
		{
			float powerSingleRotate = 1.2f * simulationStep;

			if (powerOfCrashRotate.second < 0)
				powerSingleRotate = -powerSingleRotate;

			car->rotate(powerSingleRotate);
			powerOfCrashRotate.first += powerSingleRotate / 1.f * simulationStep;
		}

		if (powerOfCrashMove.second > 0)
			car->move(powerOfCrashMove.first / 4.f * simulationStep * 2.f);

		car->getTireClass()->setTraces();
	}

	powerOfCrashMove.second *= 0.9f;
	powerOfCrashMove.first *= 0.9f;

	if (fabs(powerOfCrashMove.second) < 0.021f)
	{
		powerOfCrashMove.first = sf::Vector2f(0, 0);
		powerOfCrashMove.second = 0;
	}

	carWithWall::checkCollisions(car);

	if (*SPEED < 0.02) // eliminate bugs ;/
	{
		*speedf = 0;
		*speedb = 0;
	}
	
	for (size_t i = 0;i < 8;++i)
		car->getHitboxClass()->getBoolIsCollision(static_cast<Hitbox::collisionSide>(i)) = false;

	collideSide = Hitbox::collisionSide::None;
}

void Movement::acceleratingFunction(double *speed, double *counterSpeed, const double MAX_SPEED, bool &stateKey)
{
	stateKey = true;
	if (*counterSpeed)
	{
		if (*counterSpeed - *breakingForce >= 0)
			*counterSpeed -= *breakingForce;
		else
			*counterSpeed = 0;
	}
	else
	{
		if (*speed + *acceleration <= MAX_SPEED)
			*speed += *acceleration;
		else
			*speed = MAX_SPEED;
	}
}

void Movement::breakingFunction(double * speed, double breakValue, double minSpeed)
{
	if (!breakValue)
		breakValue = *this->breakingForce / 3;

	if (*speed < minSpeed)
		*speed += *acceleration;
	else
	{
		if (*speed - breakValue >= minSpeed)
			*speed -= breakValue;
		else *speed = minSpeed;
	}
}

sf::Vector2f Movement::getMovementVector(float rotation)
{
	sf::Vector2f v;
	float rad = toRad(rotation);

	v.x = std::sin(rad);
	v.y = -std::cos(rad);

	return v;
}

float Movement::toRad(float degrees)
{
	return (degrees*PI) / 180.f;
}
