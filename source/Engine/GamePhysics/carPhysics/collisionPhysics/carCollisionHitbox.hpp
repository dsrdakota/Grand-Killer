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