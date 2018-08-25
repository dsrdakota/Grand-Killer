#pragma once

#include <SFML/Graphics.hpp>
#include "../Collider/Collider.hpp"
#include "../Rigidbody/Rigidbody.hpp"

class Car;
class Moveable
{
public:

	enum class StateMoving
	{
		Front,
		Back,
		Stop
	};

	StateMoving movingState;

	const float &getMaxSpeed() const;
	const float getSpeed() const;
	const sf::Vector2f getMovementVector() const;

	const StateMoving &getStateMoving() const;

	void setSpeed(const float &speed);

	void gas();
	void brake();
	void slack();
	void handBrake();

//protected:

	Car *car;

	Rigidbody * rigidbody;
	Collider *collider;

	sf::Vector2f movementVector;
	float speedf, speedb; // f - front , b - back

	float acceleration; // not const cuz can do car tuning ;d
	float breakingForce;
	float MAX_SPEED; // not const cuz can do car tuning ;d

	Moveable(Car *car);
	~Moveable();

	virtual const sf::Vector2f getPosition() const = 0;
	virtual const float getRotation() const = 0;

	virtual void move(const sf::Vector2f& offset) const = 0;
	virtual void rotate(const float &angle) const = 0;

	void acceleratingFunction(float &speed, float &counterSpeed, const float &MAX_SPEED);
	void breakingFunction(float &speed, float breakValue = 0, const float &minSpeed = 0);

	void setStateMoving();
	const float toRad(const float &degrees) const;
};