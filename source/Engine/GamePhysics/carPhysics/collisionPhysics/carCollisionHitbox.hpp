#pragma once

#include <SFML/Graphics.hpp>

#include "../../../Car/Car.hpp"
#include "carCollisionWithWall.hpp"

class carCollisionHitbox
{
public:

	carCollisionHitbox(Car *car);

	std::vector<sf::CircleShape*> getOneCollisionHitbox(const Car::hitboxPosition &pos);
	Car::collisionSide *getLastCollisionSide();
	const std::vector<sf::CircleShape*> getAllHitboxes();

	static void moveHitboxes(Car *car, const sf::Vector2f &offset);
	static void rorateHitboxes(Car *car, const double &angle);
	static void rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle);
	static void moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset);

	static sf::Vector2f getCenterOfHitbox(const sf::CircleShape & hitbox);

	void update();
	void draw();

private:

	Car * car;

	std::vector<sf::CircleShape*>allHitboxes;

	std::vector<sf::CircleShape*>frontHitboxes;
	std::vector<sf::CircleShape*>upRightHitboxes;
	std::vector<sf::CircleShape*>rightHitboxes;
	std::vector<sf::CircleShape*>downRightHitboxes;
	std::vector<sf::CircleShape*>backHitboxes;
	std::vector<sf::CircleShape*>downLeftHitboxes;
	std::vector<sf::CircleShape*>leftHitboxes;
	std::vector<sf::CircleShape*>upLeftHitboxes;

	std::vector<std::vector<sf::CircleShape*>> allHitboxInOneVector;

	Car::collisionSide lastCollisionSide;
};