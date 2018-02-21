#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Car/Car.hpp"

class Movement
{
public:

	enum class TypeOfDrive
	{
		Front,
		Back
	};

	Movement(Car *car);
	~Movement();

	const double* getSpeed();
	void setSpeed(const float &speed);
	const double* getMaxSpeed();
	int getTypeOfDrive() { return static_cast<int>(drive); };
	int getStateMoving() { return static_cast<int>(*movingState); }

	void setPowerOfCrashMove(const std::pair<sf::Vector2f, float> &power) { powerOfCrashMove = power; }
	void setPowerOfCrashRotate(const std::pair<float,float>&power) { powerOfCrashRotate = power; }

	bool isRotateAble() { return rotateAble; }
	bool isMoveAble() { return moveAble; }

	void updatePosition();

	void gas(const sf::Keyboard::Key &key);
	void brake(const sf::Keyboard::Key &key = sf::Keyboard::S);
	void handBrake(const sf::Keyboard::Key &key);

	sf::Vector2f getMovementVector(float rotation);

private:

	double *speedf, *speedb; // f - front , b - back
	double *acceleration; // not const cuz can do car tuning ;d
	double *breakingForce; // can change in options
	const double *MAX_SPEED;

	std::pair<sf::Vector2f,float> powerOfCrashMove;
	std::pair<float, float> powerOfCrashRotate;

	std::pair<sf::CircleShape*, sf::CircleShape*>tiresDrive; 

	TypeOfDrive drive;

	enum class stateMoving
	{
		front,
		back,
		stop
	};

	bool moveAble;
	bool rotateAble;

	stateMoving *movingState;

	bool stateKeyGas; // true - pressed , false - realsed
	bool stateKeyBrake; // -||-
	void move();
	void setStateMoving();
	void acceleratingFunction(double *speed, double *counterSpeed, const double MAX_SPEED,bool &stateKey); // example speedf & speedb < - counter
	void breakingFunction(double * speed, double breakValue = 0, double minSpeed = 0);
	sf::Vector2f giveMeCenterOfHitbox(sf::CircleShape * hitbox);
	float toRad(float degrees);

	// dont delete

	Car *car;
};