#pragma once

#include <SFML/Graphics.hpp>
#include "../Car/Car.hpp"

class Collision
{
public:

	Collision(Car *car);
	~Collision();

	void checkCollisions();
	void draw();

private:

	sf::Image *collsisionArea;

	std::vector<std::pair<sf::CircleShape*, unsigned int>>upHitboxes;
	std::vector<std::pair<sf::CircleShape*, unsigned int>>upRightHitboxes;
	std::vector<std::pair<sf::CircleShape*, unsigned int>>rightHitboxes;
	std::vector<std::pair<sf::CircleShape*, unsigned int>>downRightHitboxes;
	std::vector<std::pair<sf::CircleShape*, unsigned int>>downHitboxes;
	std::vector<std::pair<sf::CircleShape*, unsigned int>>downLeftHitboxes;
	std::vector<std::pair<sf::CircleShape*, unsigned int>>leftHitboxes;
	std::vector<std::pair<sf::CircleShape*, unsigned int>>upLeftHitboxes;

	Car *car;
	
	void setHitbox(std::vector<std::pair<sf::CircleShape*, unsigned int>>&hitbox, const sf::Vector2f &range, const sf::Color &color = sf::Color::White);

	Car::collisionSide whereIsCollision();
};