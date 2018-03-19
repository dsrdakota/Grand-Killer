#pragma once

#include <SFML/Graphics.hpp>

class Car;

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

	void gas();
	void brake();
	void slack();
	void handBrake();

	sf::Vector2f getMovementVector(float rotation = 361);

private:

	double *speedf, *speedb; // f - front , b - back

	double *acceleration; // not const cuz can do car tuning ;d
	double *breakingForce;
	const double *MAX_SPEED;

	TypeOfDrive drive;

	std::pair<sf::Vector2f,float> powerOfCrashMove;
	std::pair<float, float> powerOfCrashRotate;

	std::pair<sf::CircleShape*, sf::CircleShape*>tiresDrive; 

	enum class stateMoving
	{
		front,
		back,
		stop
	};

	bool moveAble;
	bool rotateAble;

	stateMoving *movingState;

	void move();
	void setStateMoving();
	void acceleratingFunction(double *speed, double *counterSpeed, const double MAX_SPEED, bool &stateKey);
	void breakingFunction(double * speed, double breakValue = 0, double minSpeed = 0);
	float toRad(float degrees);

	Car *car;
};