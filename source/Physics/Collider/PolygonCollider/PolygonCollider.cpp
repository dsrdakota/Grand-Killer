#include "PolygonCollider.hpp"

PolygonCollider::PolygonCollider(std::vector<sf::Vector2f> pointPositions, const sf::Vector2f &origin)
{
	type = Type::PolygonCollider;

	shape = new sf::ConvexShape(pointPositions.size());
	for (size_t i = 0; i < pointPositions.size();++i)
	{
		shape->setPoint(i, pointPositions[i]);

		sf::CircleShape *point = new sf::CircleShape(2);
		point->setFillColor(sf::Color::Red);
		point->setOrigin(origin - pointPositions[i] + sf::Vector2f(point->getRadius(), point->getRadius()));
		point->setPosition(origin);

		points.push_back(point);
	}

	points.push_back(new sf::CircleShape(*points[0]));

	shape->setFillColor(sf::Color(0, 0, 0, 0));
	shape->setOutlineThickness(1);
	shape->setOutlineColor(sf::Color::Green);
	shape->setOrigin(origin);
	shape->setPosition(origin);
}

PolygonCollider::~PolygonCollider()
{
	delete shape;
}

void PolygonCollider::move(const sf::Vector2f & offset)
{
	shape->move(offset);

	for (auto point : points)
		point->move(offset);
}

void PolygonCollider::rotate(const float & angle)
{
	shape->rotate(angle);

	for (auto point : points)
		point->rotate(angle);
}

void PolygonCollider::setFillColor(const sf::Color & color)
{
	shape->setOutlineColor(color);
}

void PolygonCollider::draw(sf::RenderWindow & window)
{
	window.draw(*shape);

	for (auto point : points)
		window.draw(*point);
}

sf::Vector2f PolygonCollider::getCenterOfCircle(const sf::CircleShape * circle)
{
	return sf::Vector2f(circle->getGlobalBounds().left + circle->getGlobalBounds().width / 2.f,
		circle->getGlobalBounds().top + circle->getGlobalBounds().height / 2.f);
}

bool PolygonCollider::isBeetwen(const sf::CircleShape *begin, const sf::CircleShape *end, const sf::Vector2f &point)
{
	sf::Vector2f beginPosition = getCenterOfCircle(begin);
	sf::Vector2f endPosition = getCenterOfCircle(end);

	if (point.x >= beginPosition.x - 0.001f && point.x <= endPosition.x + 0.001f &&
		point.y >= beginPosition.y - 0.001f && point.y <= endPosition.y + 0.001f)
		return true;

	if (point.x >= endPosition.x - 0.001f && point.x <= beginPosition.x + 0.001f &&
		point.y >= endPosition.y - 0.001f && point.y <= beginPosition.y + 0.001f)
		return true;

	if (point.x >= beginPosition.x - 0.001f && point.x <= endPosition.x + 0.001f &&
		point.y >= endPosition.y - 0.001f && point.y <= beginPosition.y + 0.001f)
		return true;

	if (point.x >= endPosition.x - 0.001f && point.x <= beginPosition.x + 0.001f &&
		point.y >= beginPosition.y - 0.001f && point.y <= endPosition.y + 0.001f)
		return true;
	return false;
}

std::vector<sf::CircleShape*> PolygonCollider::getPoints()
{
	return points;
}

const sf::Vector2f & PolygonCollider::getPosition()
{
	return shape->getPosition();
}

