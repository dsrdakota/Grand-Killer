#pragma once

#include <SFML/Graphics.hpp>

#include "../Moveable/Moveable.hpp"

#include "../Collider/CircleCollider/CircleCollider.hpp"
#include "../Collider/PolygonCollider/PolygonCollider.hpp"

class CollisionChecker
{
public:

	static void checkCollision();

private:

	static bool checkCollision(const Collider *c1, const Collider *c2);

	static bool circlesCollision(CircleCollider *c1, CircleCollider *c2);
	static bool circleWithPolygonCollision(CircleCollider *circle, PolygonCollider *polygon);
	static bool polygonsCollision(PolygonCollider *p1, PolygonCollider *p2);

	static std::vector<Moveable*>::iterator find(std::vector<Moveable*> &vector, const Moveable * element);
};