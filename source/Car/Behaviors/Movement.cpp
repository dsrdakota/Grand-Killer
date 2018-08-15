#include "Movement.hpp"

#include "../../States/Play/Game/mGame.hpp"

#include "../../Map/Map.hpp"

#include "../Car.hpp"
#include <iostream>

#define PI 3.14159265359f

Movement::Movement(Car *car) : car(car)
{
	speedf = new float(0);
	speedb = new float(0);

	movingState = new stateMoving(stateMoving::stop);

	MAX_SPEED = new float(CarConfig::getValue(car->getName(), "MAX_SPEED"));
	acceleration = new float(CarConfig::getValue(car->getName(), "acceleration"));
	breakingForce = new float(CarConfig::getValue(car->getName(), "breakingForce"));
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

const float * Movement::getSpeed()
{
	float *speed = new float(0);
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

const float * Movement::getMaxSpeed()
{
	return MAX_SPEED;
}

void Movement::updatePosition()
{
	setStateMoving();
	move();
}

void Movement::gas()
{
	if (!car->getToTurnClass()->getSlidePhycics()->getSlideBool() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		acceleratingFunction(speedf, speedb, *MAX_SPEED, car->getDriver()->getBehaviors()->getStateKeyGas());
	else
		breakingFunction(speedf, 0.1, 5);
}

void Movement::brake()
{
	if (*speedf <= 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		acceleratingFunction(speedb, speedf, *MAX_SPEED / 2, car->getDriver()->getBehaviors()->getStateKeyGas());
	else
	{
		breakingFunction(speedf, *breakingForce, 0);
		
		//breakingFunction(speedf, *breakingForce / 3, 0); // grass
	}
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
	//if (!Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*tiresDrive.first)) ||
		//!Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*tiresDrive.second)))
	breakingFunction(speedf, 0.18f, 0); // asphalt
	//else
		//breakingFunction(speedf, 0.1, 0); // grass
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
	sf::Vector2f w = getMovementVector(car->getSprite()->getRotation() - static_cast<float>(*car->getToTurnClass()->getSlidePhycics()->getOverSteer()));

	float *SPEED = nullptr;
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

	car->move(w * *SPEED);
}

void Movement::acceleratingFunction(float *speed, float *counterSpeed, const float MAX_SPEED, bool &stateKey)
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

void Movement::breakingFunction(float * speed, float breakValue, float minSpeed)
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
