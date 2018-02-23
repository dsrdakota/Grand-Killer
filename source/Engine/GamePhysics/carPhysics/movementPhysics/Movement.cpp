#include "Movement.hpp"

#include "../collisionPhysics/carCollisionHitbox.hpp"
#include "../collisionPhysics/carCollisionWithCar.hpp"
#include "../collisionPhysics/carCollisionWithWall.hpp"
#include "../../../GameStates/Menu/Play/Game/mGame.hpp"

#define PI 3.14159265359f

Movement::Movement(Car *car) : car(car)
{
	speedf = new double(0);
	speedb = new double(0);

	movingState = new stateMoving(stateMoving::stop);

	switch (*car->getType())
	{
	case carType::Type::Ambulance:

		MAX_SPEED = new double(16);

		acceleration = new double(0.07);
		breakingForce = new double(0.4);

		break;
	case carType::Type::Audi:

		MAX_SPEED = new double(23);

		acceleration = new double(0.1);
		breakingForce = new double(0.4);

		drive = TypeOfDrive::Back;

		break;
	case carType::Type::Black_viper:

		MAX_SPEED = new double(21);

		acceleration = new double(0.09);
		breakingForce = new double(0.4);

		drive = TypeOfDrive::Back;

		break;
	case carType::Type::Car:

		MAX_SPEED = new double(20);

		acceleration = new double(0.12);
		breakingForce = new double(0.4);

		drive = TypeOfDrive::Back;

		break;
	case carType::Type::Mini_truck:

		MAX_SPEED = new double(15);

		acceleration = new double(0.06);
		breakingForce = new double(0.4);

		drive = TypeOfDrive::Front;

		break;
	case carType::Type::Police:

		MAX_SPEED = new double(21);

		acceleration = new double(0.11);
		breakingForce = new double(0.4);

		drive = TypeOfDrive::Back;

		break;
	case carType::Type::Taxi:

		MAX_SPEED = new double(17);

		acceleration = new double(0.085);
		breakingForce = new double(0.4);

		drive = TypeOfDrive::Back;

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
				breakingFunction(speedf, 0.18);
			else if (*speedb)
				breakingFunction(speedb,0.1);
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

	auto &allCars = mGame::Instance().getAllCars();
	bool breakLoop = false;
	rotateAble = true;
	moveAble = true;

	Car::collisionSide firstCheckingSide = Car::collisionSide::None;
	Car::collisionSide secondCheckingSide = Car::collisionSide::None;

	if (powerOfCrashRotate.second > 0) // right rotate
	{
		firstCheckingSide = Car::collisionSide::RightUp;
		secondCheckingSide = Car::collisionSide::LeftDown;
	}
	else if (powerOfCrashRotate.second < 0) // left rotate
	{
		firstCheckingSide = Car::collisionSide::LeftUp;
		secondCheckingSide = Car::collisionSide::RightDown;
	}

	// some car simulation like in Box2d ;d

	const float simulationStep = 0.75f;

	for (float i = 1;i <= 4;i += simulationStep)
	{
		v = w * static_cast<float>(SPEED) / 4.f * simulationStep;
		carCollisionHitbox::moveHitboxes(car, v);

		auto resultWithWall = carCollisionWithWall::checkCollisions(car, false);

		if (resultWithWall != Car::collisionSide::None)
			powerOfCrashMove = std::make_pair(sf::Vector2f(0, 0), 0.f);

		if (powerOfCrashRotate.second != 0)
		{
			if (resultWithWall == firstCheckingSide ||
				resultWithWall == secondCheckingSide)
				rotateAble = false;
		}

		for (const auto &j : allCars)
		{
			auto resultWithCars = carCollisionWithCar::checkCollisions(car, j);
			if (resultWithCars != Car::collisionSide::None)
			{
				if ((resultWithCars == Car::collisionSide::Front ||
					resultWithCars == Car::collisionSide::LeftUp ||
					resultWithCars == Car::collisionSide::RightUp) &&
					*movingState == stateMoving::front)
					breakLoop = true;

				else if ((resultWithCars == Car::collisionSide::Back ||
					resultWithCars == Car::collisionSide::LeftDown ||
					resultWithCars == Car::collisionSide::RightDown) &&
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
			float powerSingleRotate = 1.f * simulationStep;

			if (powerOfCrashRotate.second < 0)
				powerSingleRotate = -powerSingleRotate;

			car->rotate(powerSingleRotate);
			powerOfCrashRotate.first += powerSingleRotate / 1.f * simulationStep;
		}

		if (powerOfCrashMove.second > 0)
			car->move(powerOfCrashMove.first / 4.f * simulationStep);

		car->getTires()->setTraces();
	}

	powerOfCrashMove.second *= 0.6f;
	powerOfCrashMove.first *= 0.6f;

	if (fabs(powerOfCrashMove.second) < 0.021f)
	{
		powerOfCrashMove.first = sf::Vector2f(0, 0);
		powerOfCrashMove.second = 0;
	}

	carCollisionWithWall::checkCollisions(car);

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
