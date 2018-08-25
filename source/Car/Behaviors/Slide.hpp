#pragma once

#include <SFML/Graphics.hpp>

class Car;

class Slide
{
public:

	Slide(Car *car);

	const float getOverSteer();
	const int getOverSteerSide();
	const bool getSlideBool();
	float& getBreakingForceOfSlide();
	void breakSlide();
	void setOverSteer(const int &drivingStatus);
	void setPowerOfSlide(std::pair<sf::CircleShape*, sf::CircleShape*>hitbox);

private:

	enum class Status
	{
		TurningLeft,
		TurningRight,
		Straight
	};

	Car *car;

	const float MAX_OVERSTEER_LEFT, MAX_OVERSTEER_RIGHT;
	float overSteerLeft, overSteerRight;
	float powerDoingSlide;
	float powerReduceSlide;
	bool isSlide;

	float breakingForce;

	void reduceOverSteer();
	void doSlide(const float &angle, float &overSteer, const float &MAX_OVERSTEER);
	void reduceSlide(const float&angle, float &overSteer);
	void isTireOnGrass(sf::CircleShape * hitbox, float &powerDoing, float &powerReduce);
};