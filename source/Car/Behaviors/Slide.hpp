#pragma once

#include <SFML/Graphics.hpp>

class Car;

class Slide
{
public:

	Slide(Car *car);
	~Slide();

	const double* getOverSteer();
	const int getOverSteerSide();
	const bool isSlideBool();
	double *getBreakingForceOfSlide();
	void breakSlide();
	void setOverSteer(const int &drivingStatus, const bool canDoSlide);
	void setPowerOfSlide(std::pair<sf::CircleShape*, sf::CircleShape*>hitbox);

private:

	enum class Status
	{
		TurningLeft,
		TurningRight,
		Straight
	};

	Car *car;

	const double *MAX_OVERSTEER_LEFT, *MAX_OVERSTEER_RIGHT;
	double *overSteerLeft, *overSteerRight;
	double *powerDoingSlide;
	double *powerReduceSlide;
	bool isSlide;

	double *breakingForce;

	void reduceOverSteer();
	void doSlide(const double &angle, double *overSteer, const double *MAX_OVERSTEER);
	void reduceSlide(const double&angle, double *overSteer);
	void isTireOnGrass(sf::CircleShape * hitbox, double &powerDoing, double &powerReduce);
};