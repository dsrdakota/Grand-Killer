#pragma once

#include <SFML/Graphics.hpp>
#include "../Car/Car.hpp"

class Collision
{
public:

	Collision(Car *car);
	~Collision();

	void draw();

private:

	std::vector<sf::CircleShape*>upHitboxes;
	std::vector<sf::CircleShape*>upRightHitboxes;
	std::vector<sf::CircleShape*>rightHitboxes;
	std::vector<sf::CircleShape*>downRightHitboxes;
	std::vector<sf::CircleShape*>downHitboxes;
	std::vector<sf::CircleShape*>downLeftHitboxes;
	std::vector<sf::CircleShape*>leftHitboxes;
	std::vector<sf::CircleShape*>upLeftHitboxes;
	
	Car *car;
};