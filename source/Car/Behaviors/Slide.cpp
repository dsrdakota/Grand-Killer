#include "Slide.hpp"

#include "../../Map/Map.hpp"

#include "../Car.hpp"

Slide::Slide(Car * car) : MAX_OVERSTEER_LEFT(-60), MAX_OVERSTEER_RIGHT(60)
{
	this->car = car;
	overSteerLeft = 0;
	overSteerRight = 0;
	powerDoingSlide = 0.5;
	powerReduceSlide = 1;
	isSlide = false;

	breakingForce = 0;
}

const float Slide::getOverSteer()
{
	float overSteer = 0;

	if (fabs(overSteerLeft) >0 && fabs(overSteerRight) <= 0)
		return overSteerLeft;
	else if (fabs(overSteerRight) >0 && fabs(overSteerLeft) <= 0)
		return overSteerRight;

	return overSteer;
}

const int Slide::getOverSteerSide()
{
	if (fabs(overSteerLeft) >0 && fabs(overSteerRight) <= 0)
		return 1;
	else if (fabs(overSteerRight) >0 && fabs(overSteerLeft) <= 0)
		return 2;
	return 0;
}

const bool Slide::getSlideBool()
{
	return isSlide;
}

float& Slide::getBreakingForceOfSlide()
{
	return breakingForce;
}

void Slide::breakSlide()
{
	overSteerLeft = 0;
	overSteerRight = 0;
}

void Slide::setOverSteer(const int & drivingStatus)
{
	//if (!car->getMovementClass()->getTypeOfDrive())
		//setPowerOfSlide(std::make_pair(car->getTireClass()->getTiresPos(0), car->getTireClass()->getTiresPos(1)));

	//else
		setPowerOfSlide(std::make_pair(car->getTireClass()->getTiresPos(2), car->getTireClass()->getTiresPos(3)));

	if (car->getSpeed() > 1 && car->getStateMoving() != Moveable::StateMoving::Stop &&
		(car)->getSpeed() > car->getMaxSpeed() * 0.92f || // car on asphalt
			isSlide ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && car->getSpeed() > 0)) //||
			//(car->getMovementClass()->getTypeOfDrive() ?
				//Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*car->getTireClass()->getTiresPos(2))) && Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*car->getTireClass()->getTiresPos(3)))
				//: Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*car->getTireClass()->getTiresPos(0))) && Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*car->getTireClass()->getTiresPos(1))))))
	{
		Status status = static_cast<Status>(drivingStatus);
		if (status == Status::TurningLeft)
		{
			if (fabs(overSteerRight) <= 0)
				doSlide(-powerDoingSlide, overSteerLeft, MAX_OVERSTEER_LEFT);
			else
				reduceSlide(-(powerReduceSlide * 2), overSteerRight);
		}
		else if (status == Status::TurningRight)
		{
			if (fabs(overSteerLeft) <= 0)
				doSlide(powerDoingSlide, overSteerRight, MAX_OVERSTEER_RIGHT);
			else
				reduceSlide(powerReduceSlide * 2, overSteerLeft);
		}
		else
		{
			if (overSteerLeft && !overSteerRight)
				reduceSlide(powerReduceSlide, overSteerLeft);
			else
				overSteerLeft = 0;

			if (overSteerRight && !overSteerLeft)
				reduceSlide(-powerReduceSlide, overSteerRight);
			else
				overSteerRight = 0;

			if (!overSteerRight && !overSteerLeft)
				isSlide = false;
		}
	}
	else
	{
		if (overSteerLeft && !overSteerRight)
			reduceSlide(powerReduceSlide, overSteerLeft);
		else
			overSteerLeft = 0;

		if (overSteerRight && !overSteerLeft)
			reduceSlide(-powerReduceSlide, overSteerRight);
		else
			overSteerRight = 0;

		if (!overSteerRight && !overSteerLeft)
			isSlide = false;

		if (car->getSpeed() <= 0)
		{
			overSteerLeft = 0;
			overSteerRight = 0;
			isSlide = false;
		}
	}
}

void Slide::setPowerOfSlide(std::pair<sf::CircleShape*, sf::CircleShape*>hitbox)
{
	// R 133 G 91 B 0

	float PowerDoingOfBothHitbox = 0;
	float PowerReduceOfBothHitbox = 0;

	isTireOnGrass(hitbox.first, PowerDoingOfBothHitbox, PowerReduceOfBothHitbox);
	isTireOnGrass(hitbox.second, PowerDoingOfBothHitbox, PowerReduceOfBothHitbox);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		PowerDoingOfBothHitbox += 2.f;

	powerDoingSlide = PowerDoingOfBothHitbox / 2.f;
	powerReduceSlide = PowerReduceOfBothHitbox / 2.f;
}

void Slide::doSlide(const float &angle, float &overSteer, const float &MAX_OVERSTEER)
{
	if (fabs(overSteer) < fabs(MAX_OVERSTEER))
	{
		if (fabs(overSteer) + -fabs(angle) <= fabs(MAX_OVERSTEER))
			overSteer += angle;
		else
			overSteer = MAX_OVERSTEER;
		car->rotate(angle);

		breakingForce += 0.1f;

		if (fabs(overSteer) >= 5)
			isSlide = true;
	}
}

void Slide::reduceSlide(const float &angle, float &overSteer)
{
	if (fabs(overSteer) > 0)
	{
		if (fabs(overSteer) + -fabs(angle) >= 0)
			overSteer += angle;
		else
			overSteer = 0;

		isSlide = false;

		if (breakingForce - 0.1f > 0)
			breakingForce -= 0.1f;
	}
}

void Slide::isTireOnGrass(sf::CircleShape * hitbox, float &powerDoing, float &powerReduce)
{
	const float POWER_DOING_ON_ASPHALT = 0.3f;
	const float POWER_DOING_ON_GRASS = 0.4f;

	const float POWER_REDUCE_ON_ASPHALT = 0.7f;
	const float POWER_REDUCE_ON_GRASS = 0.6f;

	//if (Map::isPointOnGrass(Hitbox::getCenterOfHitbox(*hitbox)))
	{
		powerDoing += POWER_DOING_ON_GRASS;
		powerReduce += POWER_REDUCE_ON_GRASS;
	}

	//else
	{
		//powerDoing += POWER_DOING_ON_ASPHALT;
		//powerReduce += POWER_REDUCE_ON_ASPHALT;
	}
}