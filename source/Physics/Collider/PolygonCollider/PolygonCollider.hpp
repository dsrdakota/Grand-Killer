#pragma once

#include "../Collider.hpp"

class PolygonCollider : public Collider
{
public:
	
	PolygonCollider(std::vector<sf::Vector2f>pointPositions, const sf::Vector2f &origin);
	~PolygonCollider();

	static sf::Vector2f getCenterOfCircle(const sf::CircleShape *circle);
	static bool isBeetwen(const sf::CircleShape *begin, const sf::CircleShape *end, const sf::Vector2f &point);
	std::vector<sf::CircleShape*> getPoints();

	const sf::Vector2f& getPosition() override;

	void move(const sf::Vector2f &offset) override;
	void rotate(const float &angle) override;
	void setFillColor(const sf::Color &color) override;
	void draw(sf::RenderWindow &window) override;

	sf::ConvexShape *shape;

private:

	std::vector<sf::CircleShape*>points;
};