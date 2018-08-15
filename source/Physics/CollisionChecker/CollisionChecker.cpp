#include "CollisionChecker.hpp"

#include "../../Engine/Engine.hpp"
#include "../../Tools/Equation.hpp"

#include "../CollisionSolver/CollisionSolver.hpp"

sf::Vector2f pointOfCollision;

void CollisionChecker::checkCollision()
{
	for (const auto object1 : World::Instance().getObjects())
	{
		if (object1->collider == nullptr)
			continue;

		for (const auto object2 : World::Instance().getObjects())
		{
			if (object2->collider == nullptr)
				continue;

			if (object1 == object2)
				continue;

			auto resultOfThis = find(object1->collider->collideObjects, object2);
			auto resultOfCollider = find(object2->collider->collideObjects, object1);

			if (checkCollision(object1->collider, object2->collider))
			{
				if (resultOfThis == object1->collider->collideObjects.end() &&
					resultOfCollider == object2->collider->collideObjects.end())
				{
					object1->collider->collideCount++;
					object2->collider->collideCount++;

					object1->collider->collideObjects.push_back(object2);
					object2->collider->collideObjects.push_back(object1);

					object1->collider->setFillColor(sf::Color::Red);
					object2->collider->setFillColor(sf::Color::Red);

					//object1->rigidbody->clearForces();
					//object2->rigidbody->clearForces();
				}

				object1->rigidbody->clearForces();
				object2->rigidbody->clearForces();

				CollisionSolver::solve(object1, object2, pointOfCollision);
			}
			else
			{
				if (resultOfThis != object1->collider->collideObjects.end() &&
					resultOfCollider != object2->collider->collideObjects.end())
				{
					object1->collider->collideCount--;
					object2->collider->collideCount--;

					object1->collider->collideObjects.erase(resultOfThis);
					object2->collider->collideObjects.erase(resultOfCollider);

					object1->collider->setFillColor(sf::Color::Green);
					object2->collider->setFillColor(sf::Color::Green);
				}
			}
		}
	}
}

bool CollisionChecker::checkCollision(const Collider * c1, const Collider * c2)
{
	if (c1->type == Collider::Type::CircleCollider && c2->type == Collider::Type::CircleCollider)
		return circlesCollision((CircleCollider*)(c1), (CircleCollider*)(c2));

	else if (c1->type == Collider::Type::PolygonCollider && c2->type == Collider::Type::PolygonCollider)
		return polygonsCollision((PolygonCollider*)(c1), (PolygonCollider*)(c2));

	else if (c1->type == Collider::Type::CircleCollider && c2->type == Collider::Type::PolygonCollider)
		return circleWithPolygonCollision((CircleCollider*)(c1), (PolygonCollider*)(c2));

	else
		return circleWithPolygonCollision((CircleCollider*)(c2), (PolygonCollider*)(c1));

	return false;
}

bool CollisionChecker::circlesCollision(CircleCollider * c1, CircleCollider * c2)
{
	sf::Vector2f lengthVector = c1->getPosition() - c2->getPosition();
	float length = sqrt(lengthVector.x * lengthVector.x + lengthVector.y * lengthVector.y);

	if (length <= c1->getRadius() + c2->getRadius())
	{
		pointOfCollision = (c1->getPosition() + c2->getPosition()) / 2.f;
		return true;
	}

	return false;
}

bool CollisionChecker::circleWithPolygonCollision(CircleCollider * circle, PolygonCollider * polygon)
{
	auto polygonPoints = polygon->getPoints();

	auto equation = [&](const sf::CircleShape* begin, const sf::CircleShape* end)
	{
		auto beginPos = polygon->getCenterOfCircle(begin);
		auto endPos = polygon->getCenterOfCircle(end);

		Equation eq1(beginPos, sf::Vector2f(endPos.x + 0.001f, endPos.y + 0.001f));

		float a = -(1.f / eq1.a);
		float b = -a * circle->getPosition().x + circle->getPosition().y;

		Equation eq2(a, b);

		sf::Vector2f result = Equation::solveEquations(eq1, eq2);

		if (PolygonCollider::isBeetwen(begin, end, result) == false)
			return false;

		sf::Vector2f lengthVector = circle->getPosition() - result;
		float length = sqrt(lengthVector.x * lengthVector.x + lengthVector.y * lengthVector.y);

		if (length <= circle->getRadius())
		{
			pointOfCollision = result;
			return true;
		}
		return false;
	};

	auto isPointInCircle = [&](const sf::CircleShape *point)
	{
		sf::Vector2f lengthToCircleCenterVector = polygon->getCenterOfCircle(point) - circle->getPosition();
		float lengthToCircleCenter = sqrt(lengthToCircleCenterVector.x * lengthToCircleCenterVector.x + lengthToCircleCenterVector.y * lengthToCircleCenterVector.y);

		if (lengthToCircleCenter <= circle->getRadius())
		{
			pointOfCollision = (polygon->getCenterOfCircle(point) + circle->getPosition()) / 2.f;
			return true;
		}
		return false;
	};

	for (size_t i = 0;i < polygonPoints.size() - 1;++i)
	{
		if (isPointInCircle(polygonPoints[i]))
			return true;

		if (isPointInCircle(polygonPoints[i + 1]))
			return true;

		if (equation(polygonPoints[i], polygonPoints[i + 1]))
			return true;
	}

	return false;
}

bool CollisionChecker::polygonsCollision(PolygonCollider * p1, PolygonCollider * p2)
{
	auto p1Points = p1->getPoints();
	auto p2Points = p2->getPoints();

	for (size_t i = 0;i < p1Points.size() - 1;++i)
	{
		Equation l(p1->getCenterOfCircle(p1Points[i]), sf::Vector2f(p1->getCenterOfCircle(p1Points[i + 1]).x + 0.01f, p1->getCenterOfCircle(p1Points[i + 1]).y + 0.01f));

		for (size_t j = 0;j < p2Points.size() - 1;++j)
		{
			Equation k(p2->getCenterOfCircle(p2Points[j]), sf::Vector2f(p2->getCenterOfCircle(p2Points[j + 1]).x - 0.01f, p2->getCenterOfCircle(p2Points[j + 1]).y - 0.01f));

			sf::Vector2f solution = Equation::solveEquations(l, k);

			if (p1->isBeetwen(p1Points[i], p1Points[i + 1], solution) && p2->isBeetwen(p2Points[j], p2Points[j + 1], solution))
			{
				pointOfCollision = solution;
				return true;
			}
		}
	}

	return false;
}

std::vector<Moveable*>::iterator CollisionChecker::find(std::vector<Moveable*> &vector, const Moveable * element)
{
	return std::find(vector.begin(), vector.end(), element);
}
