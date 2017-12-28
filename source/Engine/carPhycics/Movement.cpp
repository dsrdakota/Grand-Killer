#include "Movement.hpp"

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
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (!car->isSlide())
			acceleratingFunction(speedf, speedb, *MAX_SPEED, stateKeyGas);
		else
			breakingFunction(speedf, 0.08 ,5);
	}
	else
		stateKeyGas = false;
}

void Movement::brake(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key))
		acceleratingFunction(speedb, speedf, *MAX_SPEED / 2, stateKeyGas);
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
	if (sf::Keyboard::isKeyPressed(key))
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
	sf::Vector2f v;
	sf::Vector2f w = getMovementVector(car->getShape()->getShape()->getRotation() - static_cast<float>(*car->getOverSteerValue()));

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

	v.x = w.x * static_cast<float>(SPEED);
	v.y = w.y * static_cast<float>(SPEED);

	car->move(v);
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
