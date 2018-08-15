#include "Moveable.hpp"

#include "../../Engine/Engine.hpp"

Moveable::Moveable()
{
	speedf = new float(0);
	World::Instance().addMoveableObject(this);
}

Moveable::~Moveable()
{
	delete rigidbody;
	delete collider;

	delete acceleration;
	delete breakingForce;

	delete speedf;
	delete speedb;
	delete MAX_SPEED;
}

const float Moveable::getSpeed() const
{
	return *speedf;
}

void Moveable::gas()
{
	
}

void Moveable::brake()
{
	
}

void Moveable::slack()
{
	
}

void Moveable::handBrake()
{
	
}