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

	sf::Image *collisionArea;

	std::vector<sf::CircleShape*>upHitboxes;
	std::vector<sf::CircleShape*>upRightHitboxes;
	std::vector<sf::CircleShape*>rightHitboxes;
	std::vector<sf::CircleShape*>downRightHitboxes;
	std::vector<sf::CircleShape*>downHitboxes;
	std::vector<sf::CircleShape*>downLeftHitboxes;
	std::vector<sf::CircleShape*>leftHitboxes;
	std::vector<sf::CircleShape*>upLeftHitboxes;

	Car *car;
	
	void setHitbox(std::vector<sf::CircleShape*>&hitbox, const sf::Vector2f &range, const sf::Color &color = sf::Color::White);

	Car::collisionSide whereIsCollision();
	bool checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>&hitbox);
	void rotateOneHitbox(const std::vector<sf::CircleShape*>&hitbox, const float &angle);
	float howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide &side);
	sf::Vector2f moveFromWall(const Car::collisionSide &side);
};