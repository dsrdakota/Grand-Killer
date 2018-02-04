#include "Movement.hpp"

#include "../collisionPhysics/Collision.hpp"

#include <iostream>

#define PI 3.14159265359f

Movement::Movement(Car *car) : car(car)
{
	speedf = new double(0);
	speedb = new double(0);

	movingState = new stateMoving(stateMoving::stop);

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

		MAX_SPEED = new double(17);

		acceleration = new double(0.085);
		breakingForce = new double(0.4);

		drive = TypeOfDrive::Back;

		break;
	case carType::Type::Truck:
		break;
	}

	if (drive != TypeOfDrive::Back)
		tiresDrive = std::make_pair(car->getTires()->getTiresPos(0), car->getTires()->getTiresPos(1));

	else
		tiresDrive = std::make_pair(car->getTires()->getTiresPos(2), car->getTires()->getTiresPos(3));
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

void Movement::updatePosition()
{
	setStateMoving();
	move();
}

void Movement::gas(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key) && !car->getBoolIsCollision(Car::collisionSide::Front))
	{
		if (!car->isSlide() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			acceleratingFunction(speedf, speedb, *MAX_SPEED, stateKeyGas);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if(!Map::isPointOnGrass(giveMeCenterOfHitbox(tiresDrive.first)) || 
				!Map::isPointOnGrass(giveMeCenterOfHitbox(tiresDrive.second)))
				breakingFunction(speedf, 0.18, 0); // asphalt
			else
				breakingFunction(speedf, 0.1, 0); // grass
		}
		else
			breakingFunction(speedf, 0.1, 5);
	}
	else
		stateKeyGas = false;
}

void Movement::brake(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key) && !car->getBoolIsCollision(Car::collisionSide::Back))
	{
		if(*speedf <= 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			acceleratingFunction(speedb, speedf, *MAX_SPEED / 2, stateKeyGas);
		else
		{
			if(!Map::isPointOnGrass(giveMeCenterOfHitbox(tiresDrive.first)) || 
				!Map::isPointOnGrass(giveMeCenterOfHitbox(tiresDrive.second))) // asphalt
				breakingFunction(speedf, *breakingForce, 0);
			else
				breakingFunction(speedf, *breakingForce /3, 0); // grass
		}
	}
	else
		stateKeyBrake = false;

	if (stateKeyBrake == false && stateKeyGas == false)
	{
		if (!car->isSlide())
		{
			if (*speedf)
				breakingFunction(speedf);
			else if (*speedb)
				breakingFunction(speedb);
		}
		else 
		{
			if (*speedf)
				breakingFunction(speedf,0.08);
			else if (*speedb)
				breakingFunction(speedb,0.08);
		}
	}
}

void Movement::handBrake(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			brake();
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
	sf::Vector2f v(0,0);
	sf::Vector2f w = getMovementVector(car->getSprite()->getRotation() - static_cast<float>(*car->getOverSteerValue()));

	double SPEED = 0;
	switch (*movingState)
	{
	case stateMoving::front:
		SPEED = *speedf;
		break;
	case stateMoving::back:
		SPEED = *speedb;
		w = -w;
		break;
	}

	v = w * static_cast<float>(SPEED);

	car->move(v);
	car->move(powerOfCrash);
	powerOfCrash.x *= 0.90f;
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

sf::Vector2f Movement::giveMeCenterOfHitbox(sf::CircleShape * hitbox)
{
	return sf::Vector2f(hitbox->getGlobalBounds().left + hitbox->getGlobalBounds().width / 2,
		hitbox->getGlobalBounds().top + hitbox->getGlobalBounds().height / 2);
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
