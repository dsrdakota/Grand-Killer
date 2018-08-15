#include "World.hpp"

#include "../../Physics/CollisionChecker/CollisionChecker.hpp"

#include <iostream>

std::vector<Moveable*> &World::getObjects()
{
	return objects;
}

void World::addMoveableObject(Moveable * object)
{
	objects.push_back(object);
}

void World::simulate()
{
	const float simulationStep = 0.75f;

	for (float i = 1;i <= 4;i += simulationStep)
	{
		for (auto object : objects)
		{
			sf::Vector2f movementVector = object->getMovementVector();

			if (object->getStateMoving() == Moveable::StateMoving::Back)
				movementVector = -movementVector;

			sf::Vector2f vector = movementVector * object->getSpeed() / 4.f * simulationStep;

			//if (vector != sf::Vector2f(0, 0) && object->collider->collideCount <= 0)
				object->move(vector);
		}

		//CollisionChecker::checkCollision();
	}

	for (auto object : objects)
	{
		object->setStateMoving();

		//object->rigidbody->applyForces();
		//object->rigidbody->applyTorques();
	}
}
