#pragma once

#include <SFML/Graphics.hpp>

#include "../Attributes/Hitbox.hpp"

#include "Movement.hpp"
#include "ToTurn.hpp"
#include "Slide.hpp"
#include "Traces.hpp"

#include <cstdarg>

class ToTurn
{
public:

	enum class Direction
	{
		Left,
		Right
	};

	enum class keyStatus
	{
		Pressed,
		Released
	};

	enum class Status
	{
		TurningLeft,
		TurningRight,
		Straight
	};

	ToTurn(Car *car);
	~ToTurn();

	keyStatus* getStatusKeyToTurn(const Direction &direction);
	Slide *getSlidePhycics();
	void turning(const Direction &direction);
	void updatePosition();

private:

	Car *car;
	std::pair<sf::Sprite*, sf::Sprite*>tiresFront;
	std::pair<sf::Sprite*, sf::Sprite*>tiresBack;

	Slide *slide;

	const double *MAX_ROTATE_TIRE;
	const double *MAX_ROTATE_CAR;

	const double *SPEED_ROTATE_TIRE;
	const double *SPEED_ROTATE_CAR;

	double *rotateCarValue;

	double *actualValueRotateLeftCar;
	double *actualValueRotateRightCar;

	double *actualValueRotateLeftTire;
	double *actualValueRotateRightTire;

	keyStatus *keyToLeftTurn;
	keyStatus *keyToRightTurn;

	Status *drivingStatus;

	void turn(sf::Sprite *tire, sf::Sprite *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar);
	void straight(sf::Sprite *tire, sf::Sprite *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar);
	void rotateCar(const float & actualValueRotateCar, const Hitbox::collisionSide &sideFirst, const Hitbox::collisionSide &sideSecond, const std::pair<std::vector<sf::CircleShape*>,std::vector<sf::CircleShape*>>&hitboxLeftRight);

	bool checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle);

	void addValue(double &value, const double &addValue, const double &max);
	void reduceValue(double &value, const double &reduceValue, const double &min);
	void resetValue(const unsigned value, ...);
};