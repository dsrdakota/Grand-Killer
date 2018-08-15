#include "CollisionSolver.hpp"

#include "../Force/Force.hpp"
#include "../../Tools/Equation.hpp"

#include <iostream>

Moveable * CollisionSolver::object1;
Moveable * CollisionSolver::object2;
sf::Vector2f & CollisionSolver::pointOfCollision = sf::Vector2f(-1, -1);

void CollisionSolver::solve(Moveable * object1, Moveable * object2, sf::Vector2f &pointOfCollision)
{
	CollisionSolver::object1 = object1;
	CollisionSolver::object2 = object2;
	CollisionSolver::pointOfCollision = pointOfCollision;

	addMoveForce();
	addRotateForce();
}

void CollisionSolver::addMoveForce()
{
	auto force1 = object1->rigidbody->getFinalForce();
	auto force2 = object2->rigidbody->getFinalForce();

	object1->rigidbody->addForce(Force(force2.getDirection(), (force1.getPower() + force2.getPower()) / 4.f));
	object2->rigidbody->addForce(Force(-force2.getDirection(), (force1.getPower() + force2.getPower()) / 8.f));

	object2->rigidbody->addForce(Force(force1.getDirection(), (force1.getPower() + force2.getPower()) / 4.f));
	object1->rigidbody->addForce(Force(-force1.getDirection(), (force1.getPower() + force2.getPower()) / 8.f));
}

void CollisionSolver::addRotateForce()
{
	calculateRotateForce(object1, object2, pointOfCollision);
	calculateRotateForce(object2, object1, pointOfCollision);
}

void CollisionSolver::calculateRotateForce(Moveable * object1, Moveable * object2, sf::Vector2f & pointOfCollision)
{
	sf::Vector2f lengthVector = pointOfCollision - object2->collider->getPosition();

	auto force1 = object1->rigidbody->getFinalForce();
	auto force2 = object2->rigidbody->getFinalForce();

	float power = (force1.getPower() + force2.getPower()) / 2.f;

	float torque = lengthVector.x * force1.getDirection().y * power - lengthVector.y * force1.getDirection().x * power;

	torque /= 200.f;

	object2->rigidbody->addTorque(torque);

	torque = lengthVector.x * force1.getDirection().y * power - lengthVector.y * force1.getDirection().x * power;

	torque /= 200.f;

	object1->rigidbody->addTorque(torque);
}
