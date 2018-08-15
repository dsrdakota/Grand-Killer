#include "CircleCollider.hpp"

CircleCollider::CircleCollider(const float & radius)
{
	type = Collider::Type::CircleCollider;

	RADIUS = new const float(radius);
	const float OUTLINE_THICKNESS = 1;
	circle = new sf::CircleShape(*RADIUS - OUTLINE_THICKNESS);
	circle->setOrigin(*RADIUS - OUTLINE_THICKNESS, *RADIUS - OUTLINE_THICKNESS);
	circle->setFillColor(sf::Color(0, 0, 0, 0));
	circle->setOutlineThickness(OUTLINE_THICKNESS);
	circle->setOutlineColor(sf::Color::Green);
}

CircleCollider::~CircleCollider()
{
	delete RADIUS;
	delete circle;
}

const sf::Vector2f & CircleCollider::getPosition()
{
	return circle->getPosition();
}

const float& CircleCollider::getRadius() const
{
	return *RADIUS;
}

void CircleCollider::move(const sf::Vector2f & offset)
{
	circle->move(offset);
}

void CircleCollider::setFillColor(const sf::Color &color)
{
	circle->setOutlineColor(color);
}

void CircleCollider::draw(sf::RenderWindow & window)
{
	if (drawable)
		window.draw(*circle);
}
