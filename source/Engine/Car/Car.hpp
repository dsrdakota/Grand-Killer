#pragma once

#include <SFML/Graphics.hpp>

#include "../../Game.hpp"
#include "../../Framework/Shapes.hpp"
#include "Door.hpp"
#include "Tire.hpp"
#include "Mirror.hpp"
#include "carType.hpp"
#include "../GameStates/Menu/Play/Game/Map.hpp"

#include "../Player/playerStates.hpp"

class carPhysics;

class Car : public playerStates
{
public: 

	Car(const carType::Type &type,const sf::Vector2f &startPos);
	~Car();

	inline carType::Type *getType() { return type; }
	inline Shape *getShape() { return shape; }
	inline Door* getDoors() { return door; }
	inline Tire* getTires() { return tire; }
	std::vector<sf::CircleShape*> getAllHitboxes();
	double getSpeed();
	void setSpeed(const float &speed);
	sf::Vector2f getMovementVector(const float &rot = 361);
	const double getMaxSpeed();
	const double *getOverSteerValue();
	const int getOverSteerSide();
	double *getBreakingForceOfSlide();
	int getTypeOfDrive();
	int getStateMoving();
	bool isSlide();

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

	bool &getBoolIsCollision(const collisionSide &side);

	void toControl() override;
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

	Door *door;

	Tire *tire;
	
	Mirror *mirror;

	carPhysics *physics;

	std::vector<sf::CircleShape*>hitboxes;

	bool isCollision[9];

	void gas(const sf::Keyboard::Key &key);
	void brake(const sf::Keyboard::Key &key);
	void handBrake(const sf::Keyboard::Key &key);
	void turnLeft(const sf::Keyboard::Key &key);
	void turnRight(const sf::Keyboard::Key &key);
};