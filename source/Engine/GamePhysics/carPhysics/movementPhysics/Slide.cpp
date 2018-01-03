#include "Slide.hpp"
Slide::Slide(Car * car)
{
	this->car = car;
	MAX_OVERSTEER_LEFT = new const double(-60);
	MAX_OVERSTEER_RIGHT = new const double(60);
	overSteerLeft = new double(0);
	overSteerRight = new double(0);
	powerDoingSlide = new double(0.5);
	powerReduceSlide = new double(1);
	isSlide = false;

	breakingForce = new double(0);
}

Slide::~Slide()
{
	delete overSteerLeft;
	delete overSteerRight;
	delete powerDoingSlide;
	delete powerReduceSlide;

	delete MAX_OVERSTEER_LEFT;
	delete MAX_OVERSTEER_RIGHT;

	delete breakingForce;
}

const double * Slide::getOverSteer()
{
	double *overSteer = new double(0);
	
	if (fabs(*overSteerLeft) >0 && fabs(*overSteerRight) <=0)
		return overSteerLeft;
	else if (fabs(*overSteerRight) >0 && fabs(*overSteerLeft) <=0)
		return overSteerRight;

	return overSteer;
}

const int Slide::getOverSteerSide()
{
	if (fabs(*overSteerLeft) >0 && fabs(*overSteerRight) <= 0)
		return 1;
	else if (fabs(*overSteerRight) >0 && fabs(*overSteerLeft) <= 0)
		return 2;
	return 0;
}

const bool Slide::getSlideBool()
{
	return isSlide;
}

double * Slide::getBreakingForceOfSlide()
{
	return breakingForce;
}

void Slide::breakSlide()
{
	*overSteerLeft = 0;
	*overSteerRight = 0;
}

void Slide::setOverSteer(const int & drivingStatus)
{
	if (!car->getTypeOfDrive())
		setPowerOfSlide(std::make_pair(car->getTires()->getTiresPos(0), car->getTires()->getTiresPos(1)));

	else
		setPowerOfSlide(std::make_pair(car->getTires()->getTiresPos(2), car->getTires()->getTiresPos(3)));

	if (car->getSpeed() > 1 && !car->getStateMoving() &&
		(car->getSpeed() > car->getMaxSpeed() * 0.92 || // car on asphalt
		isSlide ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && car->getSpeed() > 0) ||
		(car->getTypeOfDrive() ? 
		Map::isPointOnGrass(getMeCenterOfHitbox(car->getTires()->getTiresPos(2))) && Map::isPointOnGrass(getMeCenterOfHitbox(car->getTires()->getTiresPos(3)))
			: Map::isPointOnGrass(getMeCenterOfHitbox(car->getTires()->getTiresPos(0))) && Map::isPointOnGrass(getMeCenterOfHitbox(car->getTires()->getTiresPos(1))))))
	{
		Status status = static_cast<Status>(drivingStatus);
		if (status == Status::TurningLeft)
		{
			if (fabs(*overSteerRight) <= 0)
				doSlide(-*powerDoingSlide, overSteerLeft, MAX_OVERSTEER_LEFT);
			else
				reduceSlide(-(*powerReduceSlide*2), overSteerRight);
		}
		else if (status == Status::TurningRight)
		{
			if (fabs(*overSteerLeft) <= 0)
				doSlide(*powerDoingSlide, overSteerRight, MAX_OVERSTEER_RIGHT);
			else
				reduceSlide(*powerReduceSlide * 2, overSteerLeft);
		}
		else
		{
			if (*overSteerLeft && !*overSteerRight)
				reduceSlide(*powerReduceSlide, overSteerLeft);
			else
				*overSteerLeft = 0;

			if (*overSteerRight && !*overSteerLeft)
				reduceSlide(-*powerReduceSlide, overSteerRight);
			else
				*overSteerRight = 0;

			if (!*overSteerRight && !*overSteerLeft)
				isSlide = false;
		}
	}
	else
	{
		if (*overSteerLeft && !*overSteerRight)
			reduceSlide(*powerReduceSlide, overSteerLeft);
		else
			*overSteerLeft = 0;

		if (*overSteerRight && !*overSteerLeft)
			reduceSlide(-*powerReduceSlide, overSteerRight);
		else
			*overSteerRight = 0;

		if (!*overSteerRight && !*overSteerLeft)
			isSlide = false;

		if (car->getSpeed() <= 0)
		{
			*overSteerLeft = 0;
			*overSteerRight = 0;
			isSlide = false;
		}
	}
}

void Slide::setPowerOfSlide(std::pair<sf::CircleShape*, sf::CircleShape*>hitbox)
{
	// R 133 G 91 B 0

	double PowerDoingOfBothHitbox = 0;
	double PowerReduceOfBothHitbox = 0;

	isTireOnGrass(hitbox.first, PowerDoingOfBothHitbox, PowerReduceOfBothHitbox);
	isTireOnGrass(hitbox.second, PowerDoingOfBothHitbox, PowerReduceOfBothHitbox);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		PowerDoingOfBothHitbox += 2;

	*powerDoingSlide = PowerDoingOfBothHitbox / 2;
	*powerReduceSlide = PowerReduceOfBothHitbox / 2;
}

void Slide::doSlide(const double &angle, double *overSteer, const double *MAX_OVERSTEER)
{
	if (fabs(*overSteer) < fabs(*MAX_OVERSTEER))
	{
		if (fabs(*overSteer) + -fabs(angle) <= fabs(*MAX_OVERSTEER))
			*overSteer += angle;
		else
			*overSteer = *MAX_OVERSTEER;
		car->rotate(angle);

		*breakingForce += 0.1;

		if (fabs(*overSteer) >= 5)
			isSlide = true;
	}
}

void Slide::reduceSlide(const double & angle, double * overSteer)
{
	if (fabs(*overSteer) > 0)
	{
		if (fabs(*overSteer) + -fabs(angle) >= 0)
			*overSteer += angle;
		else
			*overSteer = 0;

		isSlide = false;

		if (*breakingForce - 0.1 > 0)
			*breakingForce -= 0.1;
	}
}

void Slide::isTireOnGrass(sf::CircleShape * hitbox, double &powerDoing, double &powerReduce)
{
	const double POWER_DOING_ON_ASPHALT = 0.3;
	const double POWER_DOING_ON_GRASS = 0.4;

	const double POWER_REDUCE_ON_ASPHALT = 0.7;
	const double POWER_REDUCE_ON_GRASS = 0.6;

	if (Map::isPointOnGrass(getMeCenterOfHitbox(hitbox)))
	{
		powerDoing += POWER_DOING_ON_GRASS;
		powerReduce += POWER_REDUCE_ON_GRASS;
	}

	else
	{
		powerDoing += POWER_DOING_ON_ASPHALT;
		powerReduce += POWER_REDUCE_ON_ASPHALT;
	}
}

sf::Vector2f Slide::getMeCenterOfHitbox(const sf::CircleShape * hitbox)
{
	return sf::Vector2f(hitbox->getGlobalBounds().left + hitbox->getGlobalBounds().width / 2,
		hitbox->getGlobalBounds().top + hitbox->getGlobalBounds().height / 2);
}