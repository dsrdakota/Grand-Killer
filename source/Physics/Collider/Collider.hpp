#pragma once

#include <SFML/Graphics.hpp>

class Moveable;
class Collider
{
public:

	enum class Type
	{
		CircleCollider,
		PolygonCollider
	};

	Type type;

	std::vector<Moveable*> collideObjects;
	size_t collideCount = 0;

	bool drawable = false;

	virtual const sf::Vector2f& getPosition() = 0;

	virtual void move(const sf::Vector2f &offset) = 0;
	virtual void rotate(const float & angle) = 0;
	virtual void setFillColor(const sf::Color &color) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};