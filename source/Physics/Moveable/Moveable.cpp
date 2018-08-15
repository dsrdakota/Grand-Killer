#include "Moveable.hpp"

#include "../../Engine/Engine.hpp"

#include <iostream>

Moveable::Moveable()
{
	speedf = 0;
	speedb = 0;
	World::Instance().addMoveableObject(this);
}

Moveable::~Moveable()
{
	delete rigidbody;
	delete collider;
}

const float & Moveable::getMaxSpeed() const
{
	return MAX_SPEED;
}

const float Moveable::getSpeed() const
{
	if (speedf && speedb == 0)
		return speedf;
	else if (speedb && speedf == 0)
		return speedb;
	return 0;
}

const sf::Vector2f Moveable::getMovementVector() const
{
	sf::Vector2f v;
	float rad = toRad(getRotation());

	v.x = std::sin(rad);
	v.y = -std::cos(rad);

	return v;
}

const Moveable::StateMoving & Moveable::getStateMoving() const
{
	return movingState;
}

void Moveable::setSpeed(const float & speed)
{
	if (speed > 0 && movingState != StateMoving::Stop)
	{
		switch (movingState)
		{
		case StateMoving::Front:

			if (speed < MAX_SPEED)
				speedf = speed;

			break;
		case StateMoving::Back:

			if (speed < MAX_SPEED / 2.f)
				speedb = speed;

			break;
		}
	}
	else if (speed <= 0)
	{
		speedf = 0;
		speedb = 0;
	}
}

void Moveable::gas()
{
	acceleratingFunction(speedf, speedb, MAX_SPEED);
}

void Moveable::brake()
{
	acceleratingFunction(speedb, speedf, MAX_SPEED / 2.f);
}

void Moveable::slack()
{
	if (speedf)
		breakingFunction(speedf);
	else if (speedb)
		breakingFunction(speedb);
}

void Moveable::handBrake()
{
	breakingFunction(speedf, 0.18f, 0);
}

void Moveable::acceleratingFunction(float &speed, float &counterSpeed, const float &MAX_SPEED)
{
	if (counterSpeed)
	{
		if (counterSpeed - breakingForce >= 0)
			counterSpeed -= breakingForce;
		else
			counterSpeed = 0;
	}
	else
	{
		if (speed + acceleration <= MAX_SPEED)
			speed += acceleration;
		else
			speed = MAX_SPEED;
	}
}

void Moveable::breakingFunction(float &speed, float breakValue, const float &minSpeed)
{
	if (!breakValue)
		breakValue = this->breakingForce / 3;

	if (speed < minSpeed)
		speed += acceleration;
	else
	{
		if (speed - breakValue >= minSpeed)
			speed -= breakValue;
		else speed = minSpeed;
	}
}

void Moveable::setStateMoving()
{
	if (speedf > 0 && speedb <= 0)
		movingState = StateMoving::Front;
	else if (speedb > 0)
		movingState = StateMoving::Back;
	else
		movingState = StateMoving::Stop;
}

const float Moveable::toRad(const float & degrees) const
{
	return (degrees*3.14f) / 180.f;
}