#pragma once

#include <SFML/Graphics.hpp>

#include "../Force/Force.hpp"

class Moveable;
class Rigidbody
{
public:

	Rigidbody(Moveable *object);
	~Rigidbody();

	Force* getFinalForce();

	void addForce(Force *force);

	void addTorque(const float &power);

	void clearForces();

	void applyForces();
	void applyTorques();

	void draw(sf::RenderWindow &window);

private:

	Moveable *object;

	std::vector<Force*>forces;

	float torque;
	std::vector<float>torques;
};