#pragma once

#include <SFML/Graphics.hpp>

#include "../Car/Car.hpp"
#include "Slide.hpp"
#include "TurnOrigin.hpp"
#include "Movement.hpp"
#include <cstdarg>

class toTurn
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

	toTurn(Car *car, std::pair<sf::Sprite*, sf::Sprite*>tiresFront, std::pair<sf::Sprite*, sf::Sprite*>tiresBack, std::pair<std::vector <sf::CircleShape*>, std::vector <sf::CircleShape*>> tiresHitbox, const double *speedRotateTire, const double*speedRotateCar);
	~toTurn();

	keyStatus* getStatusKeyToTurn(const Direction &direction);
	const double* getOverSteerValue();
	Slide *getSlidePhycics();
	bool isSlide();
	void turning(const Direction &direction);
	void updatePosition();

private:

	Car *car;
	sf::ConvexShape *carShape;
	std::pair<sf::Sprite*, sf::Sprite*>tiresFront;
	std::pair<std::vector <sf::CircleShape*>, std::vector <sf::CircleShape*>> tiresHitbox;
	std::pair<sf::Sprite*, sf::Sprite*>tiresBack;

	Slide *slide;

	double *speed;

	const double *SPEED_ROTATE_TIRE;
	const double *SPEED_ROTATE_CAR;
	const double *MAX_ROTATE_TIRE;
	double *MAX_ROTATE_CAR;
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
	void rotate(sf::Transformable *target, const sf::Vector2f &posTarget, const sf::Vector2f &posOrigin, const double *angle);

	void addValue(double &value, const double &addValue, const double &max);
	void reduceValue(double &value, const double &reduceValue, const double &min);
	void resetValue(const unsigned value, ...);
};