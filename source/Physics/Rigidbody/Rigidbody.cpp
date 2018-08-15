#include "Rigidbody.hpp"

#include "../Moveable/Moveable.hpp"

#include <iostream>

Rigidbody::Rigidbody(Moveable *object)
{
	this->object = object;
}

Rigidbody::~Rigidbody()
{
	
}

Force Rigidbody::getFinalForce()
{
	sf::Vector2f direction = sf::Vector2f(0, 0);
	float power = 0;
	for (auto i : forces)
	{
		direction += i.getDirection();
		power += i.getPower();
	}

	direction += object->getMovementVector();
	power += object->getSpeed();

	direction /= static_cast<float>(forces.size()) + 1;
	power /= static_cast<float>(forces.size()) + 1;

	return Force(direction, power);
}

void Rigidbody::addForce(const Force &force)
{
	forces.push_back(force);
}

void Rigidbody::addTorque(const float & power)
{
	torques.push_back(power);
}

void Rigidbody::clearForces()
{
	forces.clear();

	torques.clear();
}

void Rigidbody::applyForces()
{
	for(size_t i = 0;i<forces.size();)
	{
		object->move(forces[i].getDirection() * forces[i].getPower());

		forces[i].getPower() -= 0.09f;

		if (forces[i].getPower() <= 0)
		{
			//delete forces[i];
			forces.erase(forces.begin());
		}
		else
			++i;
	}
}

void Rigidbody::applyTorques()
{
	for (size_t i = 0;i<torques.size();)
	{
		object->rotate(torques[i]);

		if (torques[i] > 0)
			torques[i] -= 0.05f;
		else
			torques[i] += 0.05f;

		if (torques[i] <= 0)
		{
			torques.erase(torques.begin());
		}
		else
			++i;
	}
}

