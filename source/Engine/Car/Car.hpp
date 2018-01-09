#pragma once

#include <SFML/Graphics.hpp>

#include "../../Game.hpp"
#include "../../Framework/Shapes.hpp"

#include "Door.hpp"
#include "Tire.hpp"
#include "Mirror.hpp"
#include "carType.hpp"
#include "../GamePhysics/Map/Map.hpp"

#include "../Player/playerStates.hpp"

class carPhysics;

class Car : public playerStates
{
public: 

	Car(const carType::Type &type,const sf::Vector2f &startPos = sf::Vector2f(0,0));
	~Car();

	inline carType::Type *getType() { return type; }
	inline Shape *getShape() { return shape; }
	inline Shape *getShadow() { return shadow; }
	inline Door* getDoors() { return door; }
	inline Tire* getTires() { return tire; }

	std::vector<sf::CircleShape*> getAllHitboxes();
	void setSpeed(const float &speed);
	double getSpeed();
	sf::Vector2f getMovementVector(const float &rot = 361);
	const double getMaxSpeed();
	const double *getOverSteerValue();
	const int getOverSteerSide();
	double *getBreakingForceOfSlide();
	int getTypeOfDrive();
	int getStateMoving();

	bool isSlide();
	void breakSlide();

	enum class collisionSide
	{
		Front,
		Back,
		Left,
		Right,
		RightUp,
		RightDown,
		LeftUp,
		LeftDown,
		None
	};

	enum class hitboxPosition
	{
		Front,
		upRight,
		Right,
		downRight,
		Back,
		downLeft,
		Left,
		upLeft
	};

	bool &getBoolIsCollision(const collisionSide &side);
	const std::vector<sf::CircleShape*> getCollisionHitbox(const hitboxPosition &pos);
	collisionSide *getLastCollisionSide();

	std::vector<std::pair<sf::CircleShape*, std::pair<sf::Vector2f, float*>>> getDentHitbox();

	void toControl() override;
	float getRotation() override;
	void setCamera() override;
	void draw() override; 

	void setPhycics(Car *car);
	void move(const sf::Vector2f &offset);
	void rotate(const double &angle);
	void updatePosition();
	void openDoors(const Door::Side &side, const sf::Keyboard::Key &key);
	void closeDoors(const Door::Side &side, const sf::Keyboard::Key &key);

private:
	sf::RenderWindow *window;

	carType::Type *type;
	unsigned *weight;

	Shape *shape;
	Shape *shadow;

	Door *door;

	Tire *tire;
	
	Mirror *mirror;

	carPhysics *physics;

	std::vector<sf::CircleShape*>hitboxes; // hitboxes around of car

	bool isCollision[9];

	void gas(const sf::Keyboard::Key &key);
	void brake(const sf::Keyboard::Key &key);
	void handBrake(const sf::Keyboard::Key &key);
	void turnLeft(const sf::Keyboard::Key &key);
	void turnRight(const sf::Keyboard::Key &key);
};