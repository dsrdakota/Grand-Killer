#pragma once

#include <SFML/Graphics.hpp>
#include "../Collider/Collider.hpp"
#include "../Rigidbody/Rigidbody.hpp"

class Moveable
{
public:

	enum class StateMoving
	{
		Front,
		Back,
		Stop
	};

	const float getSpeed() const;
	const virtual sf::Vector2f getMovementVector() const = 0;

	void gas();
	void brake();
	void slack();
	void handBrake();

//protected:

	Rigidbody * rigidbody;
	Collider *collider;

	sf::Vector2f movementVector;
	float *speedf, *speedb; // f - front , b - back

	float *acceleration; // not const cuz can do car tuning ;d
	float *breakingForce;
	const float *MAX_SPEED;

	Moveable();
	~Moveable();

	virtual void setPosition(const sf::Vector2f &position) const = 0;
	virtual void move(const sf::Vector2f& offset) const = 0;

	virtual void setRotation(const float &angle) const = 0;
	virtual void rotate(const float &angle) const = 0;
};