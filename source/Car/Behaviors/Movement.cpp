#include "Movement.hpp"

#include "../../States/Play/Game/mGame.hpp"

#include "../../Physics/Collision/carWithWall.hpp"
#include "../../Physics/Collision/carWithCar.hpp"

#include "../../Map/Map.hpp"

#include "../Car.hpp"

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

	auto &allCars = mGame::Instance().getAllCars();
	bool breakLoop = false;
	rotateAble = true;
	moveAble = true;

	Hitbox::collisionSide firstCheckingSide = Hitbox::collisionSide::None;
	Hitbox::collisionSide secondCheckingSide = Hitbox::collisionSide::None;

	if (powerOfCrashRotate.second > 0) // right rotate
	{
		firstCheckingSide = Hitbox::collisionSide::RightUp;
		secondCheckingSide = Hitbox::collisionSide::LeftDown;
	}
	else if (powerOfCrashRotate.second < 0) // left rotate
	{
		firstCheckingSide = Hitbox::collisionSide::LeftUp;
		secondCheckingSide = Hitbox::collisionSide::RightDown;
	}

	// some car simulation like in Box2d ;d

	const float simulationStep = 0.75f;

	for (float i = 1;i <= 4;i += simulationStep)
	{
		v = w * static_cast<float>(SPEED) / 4.f * simulationStep;
		car->getHitboxClass()->moveHitboxes(v);

		auto resultWithWall = carWithWall::checkCollisions(car, false);

		if (resultWithWall != Hitbox::collisionSide::None)
			powerOfCrashMove = std::make_pair(sf::Vector2f(0, 0), 0.f);

		if (powerOfCrashRotate.second != 0)
		{
			if (resultWithWall == firstCheckingSide ||
				resultWithWall == secondCheckingSide)
				rotateAble = false;
		}

		for (const auto &j : allCars)
		{
			auto resultWithCars = carWithCar::checkCollisions(car, j);
			if (resultWithCars != Hitbox::collisionSide::None)
			{
				if ((resultWithCars == Hitbox::collisionSide::Front ||
					resultWithCars == Hitbox::collisionSide::LeftUp ||
					resultWithCars == Hitbox::collisionSide::RightUp) &&
					*movingState == stateMoving::front)
					breakLoop = true;

				else if ((resultWithCars == Hitbox::collisionSide::Back ||
					resultWithCars == Hitbox::collisionSide::LeftDown ||
					resultWithCars == Hitbox::collisionSide::RightDown) &&
					*movingState == stateMoving::back)
					breakLoop = true;

				powerOfCrashMove = std::make_pair(sf::Vector2f(0, 0), 0.f);
				moveAble = false;

				if (powerOfCrashRotate.second != 0 && rotateAble)
				{
					if (resultWithCars == firstCheckingSide ||
						resultWithCars == secondCheckingSide)
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
			car->move(powerOfCrashMove.first / 4.f * simulationStep);

		car->getTireClass()->setTraces();
	}

	powerOfCrashMove.second *= 0.2f;
	powerOfCrashMove.first *= 0.2f;

	if (fabs(powerOfCrashMove.second) < 0.021f)
	{
		powerOfCrashMove.first = sf::Vector2f(0, 0);
		powerOfCrashMove.second = 0;
	}

	carWithWall::checkCollisions(car);

	if (SPEED < 0.02) // eliminate bugs ;/
	{
		*speedf = 0;
		*speedb = 0;
	}
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
