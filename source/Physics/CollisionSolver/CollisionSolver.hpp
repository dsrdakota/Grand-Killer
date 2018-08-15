#pragma once

#include "../Moveable/Moveable.hpp"

class CollisionSolver
{
public:

	static void solve(Moveable *object1, Moveable *object2, sf::Vector2f &pointOfCollision);
	static void addMoveForce();
	static void addRotateForce();

private:

	static Moveable * object1;
	static Moveable * object2;
	static sf::Vector2f & pointOfCollision;

	static void calculateRotateForce(Moveable *object1, Moveable *object2, sf::Vector2f &pointOfCollision);
};