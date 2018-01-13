#pragma once

#include <SFML/Graphics.hpp>

#include "../../../Car/Car.hpp"
#include "Slide.hpp"
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

	toTurn(Car *car, std::pair<sf::Sprite*, sf::Sprite*>tiresFront, std::pair<sf::Sprite*, sf::Sprite*>tiresBack, const double *speedRotateTire, const double*speedRotateCar);
	~toTurn();

	keyStatus* getStatusKeyToTurn(const Direction &direction);
	const double* getOverSteerValue();
	Slide *getSlidePhycics();
	bool isSlide();
	void breakSlide();
	void turning(const Direction &direction);
	void updatePosition();

private:

	Car *car;
	sf::ConvexShape *carShape;
	std::pair<sf::Sprite*, sf::Sprite*>tiresFront;
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
	void rotateCar(const float & actualValueRotateCar, const Car::collisionSide &sideFirst, const Car::collisionSide &sideSecond, const std::pair<std::vector<sf::CircleShape*>,std::vector<sf::CircleShape*>>&hitboxLeftRight);

	bool checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>&hitbox, const float & angle);
	void rotateOneHitbox(const std::vector<sf::CircleShape*>&hitbox, const float &angle);
	sf::Vector2f getCenterOfHitbox(const sf::CircleShape &hitbox);

	void addValue(double &value, const double &addValue, const double &max);
	void reduceValue(double &value, const double &reduceValue, const double &min);
	void resetValue(const unsigned value, ...);
};