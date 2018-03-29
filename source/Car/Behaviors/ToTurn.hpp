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

	enum class Status
	{
		TurningLeft,
		TurningRight,
		Straight
	};

	ToTurn(Car *car);
	~ToTurn();

	Slide *getSlidePhycics();
	void turning(const Direction &direction);
	void updatePosition();

private:

	Car *car;
	std::pair<sf::RectangleShape*, sf::RectangleShape*>tiresFront;
	std::pair<sf::RectangleShape*, sf::RectangleShape*>tiresBack;

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

	Status *drivingStatus;

	void turn(sf::RectangleShape *tire, sf::RectangleShape *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar);
	void straight(sf::RectangleShape *tire, sf::RectangleShape *counterTire, double *actualValueRotateTire, const double &angleTire, double *actualValueRotateCar, const double *angleCar);
	void rotateCar(const float & actualValueRotateCar, const Hitbox::collisionSide &sideFirst, const Hitbox::collisionSide &sideSecond, const std::pair<std::vector<sf::CircleShape*>,std::vector<sf::CircleShape*>>&hitboxLeftRight);

	bool checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle);

	void addValue(double &value, const double &addValue, const double &max);
	void reduceValue(double &value, const double &reduceValue, const double &min);
	void resetValue(const unsigned value, ...);
};