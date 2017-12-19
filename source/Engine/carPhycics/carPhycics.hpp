#pragma once

#include <SFML/Graphics.hpp>

#include "TurnOrigin.hpp"
#include "toTurn.hpp"
#include "../../Manager/renderSprites.hpp"
#include "Movement.hpp"

class carPhycics
{
public:
	
	carPhycics(Car *car);
	~carPhycics();

	inline toTurn* getPhycicsTurn() { return turnPhycics; }
	inline Movement* getPhycicsMove() { return movePhycics; }

	void boostSpeed(const sf::Keyboard::Key &key);
	void reduceSpeed(const sf::Keyboard::Key &key);
	void handBrake(const sf::Keyboard::Key &key);
	void turn(const toTurn::Direction &direction);

	void updatePosition();
	void move(const sf::Vector2f &offset);
	void draw();

private:

	sf::ConvexShape *car;
	
	toTurn *turnPhycics;
	Movement *movePhycics;
	const double *SPEED_ROTATE_TIRE;
	const double *SPEED_ROTATE_CAR;
};