#pragma once

#include <SFML/Graphics.hpp>

#include "movementPhysics/toTurn.hpp"
#include "../../../Manager/renderSprites.hpp"
#include "movementPhysics/Movement.hpp"
#include "collisionPhysics/carCollisionHitbox.hpp"

#include <thread>

class carPhysics
{
public:
	
	carPhysics(Car *car);
	~carPhysics();

	inline toTurn* getPhysicsTurn() { return turnPhysics; }
	inline Movement* getPhysicsMove() { return movePhysics; }
	inline carCollisionHitbox* getCollisionHitboxes() { return collisionHitboxes; }

	void boostSpeed(const sf::Keyboard::Key &key);
	void reduceSpeed(const sf::Keyboard::Key &key);
	void handBrake(const sf::Keyboard::Key &key);
	void turn(const toTurn::Direction &direction);

	void updatePosition();
	void draw();

private:
	
	toTurn *turnPhysics;
	Movement *movePhysics;
	carCollisionHitbox *collisionHitboxes;

	const double *SPEED_ROTATE_TIRE;
	const double *SPEED_ROTATE_CAR;
};