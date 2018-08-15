#pragma once

#include <SFML/Graphics.hpp>

class Equation
{
public:
	// y = ax + b
	float a, b;

	Equation(const float &a, const float &b);
	Equation(sf::Vector2f A, sf::Vector2f B);
	void setEquation(sf::Vector2f A, sf::Vector2f B);

	static sf::Vector2f solveEquations(Equation A, Equation B);

private:

	float getLengthFromZero(sf::Vector2f A);
};