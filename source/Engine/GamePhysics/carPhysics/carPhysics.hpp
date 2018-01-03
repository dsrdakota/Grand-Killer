#pragma once

#include <SFML/Graphics.hpp>

#include "TurnOrigin.hpp"
#include "toTurn.hpp"
#include "../../Manager/renderSprites.hpp"
#include "Movement.hpp"
#include "Collision.hpp"

class carPhysics
{
public:
	
	carPhysics(Car *car);
	~carPhysics();

	inline toTurn* getPhysicsTurn() { return turnPhysics; }
	inline Movement* getPhysicsMove() { return movePhysics; }

	void boostSpeed(const sf::Keyboard::Key &key);
	void reduceSpeed(const sf::Keyboard::Key &key);
	void handBrake(const sf::Keyboard::Key &key);
	void turn(const toTurn::Direction &direction);

	void updatePosition();
	void move(const sf::Vector2f &offset);
	void draw();

private:

	sf::ConvexShape *car;
	
	toTurn *turnPhysics;
	Movement *movePhysics;
	Collision *collisionPhysics;

	const double *SPEED_ROTATE_TIRE;
	const double *SPEED_ROTATE_CAR;
};