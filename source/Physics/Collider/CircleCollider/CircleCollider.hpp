#pragma once

#include "../Collider.hpp"

class CircleCollider : public Collider
{
public:
	
	CircleCollider(const float &radius);
	~CircleCollider();

	const sf::Vector2f& getPosition() override;
	const float& getRadius() const;

	void move(const sf::Vector2f &offset) override;
	void rotate(const float &angle) override { ; }
	void setFillColor(const sf::Color &color) override;
	void draw(sf::RenderWindow &window) override;

protected:

	const float *RADIUS;
	sf::CircleShape *circle;
};