#include "Equation.hpp"

Equation::Equation(const float & a, const float & b)
{
	this->a = a;
	this->b = b;
}

Equation::Equation(sf::Vector2f A, sf::Vector2f B)
{
	setEquation(A, B);
}

void Equation::setEquation(sf::Vector2f A, sf::Vector2f B)
{
	sf::Vector2f begin, end;

	if (getLengthFromZero(A) < getLengthFromZero(B))
	{
		begin = A;
		end = B;
	}
	else
	{
		begin = B;
		end = A;
	}
	float y = end.x - begin.x;
	b = -begin.y * (end.x - begin.x) - (begin.y - end.y) * begin.x;
	a = (begin.y - end.y);

	b = -b / y;
	a = -a / y;
}

sf::Vector2f Equation::solveEquations(Equation A, Equation B)
{
	float x = A.a - B.a;
	float xNum = B.b - A.b;

	xNum /= x;

	return sf::Vector2f(xNum, A.a * xNum + A.b);
}

float Equation::getLengthFromZero(sf::Vector2f A)
{
	return sqrt(A.x * A.x + A.y * A.y);
}
