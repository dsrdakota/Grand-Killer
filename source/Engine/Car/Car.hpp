#pragma once

#include <SFML/Graphics.hpp>

#include "../../Game.hpp"

#include "Door.hpp"
#include "Tire.hpp"
#include "carType.hpp"
#include "../Map/Map.hpp"

#include "../Player/playerStates.hpp"

class carPhysics;

class Car : public playerStates
{
public: 

	Car(const carType::Type &type,const sf::Vector2f &startPos = sf::Vector2f(0,0));
	~Car();

	inline carType::Type *getType() { return type; }
	inline sf::Sprite *getSprite() { return sprite; }
	inline Door* getDoors() { return door; }
	inline Tire* getTires() { return tire; }

	void setSpeed(const float &speed);
	double getSpeed();
	unsigned getWeight();
	sf::Vector2f getMovementVector(const float &rot = 361);
	const double getMaxSpeed();
	const double *getOverSteerValue();
	const int getOverSteerSide();
	double *getBreakingForceOfSlide();
	int getTypeOfDrive();
	int getStateMoving();

	sf::FloatRect getGlobalBounds();

	void setPowerOfCrashMove(const sf::Vector2f &power);
	void setPowerOfCrashRotate(const std::pair<float, float>&power);

	sf::Vector2f getPowerOfCrashMove();
	float getPowerOfCrashRotate();

	bool isSlide();
	void breakSlide();

	enum class collisionSide
	{
		Front,
		RightUp,
		Right,
		RightDown,
		Back,
		LeftDown,
		Left,
		LeftUp,
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
	const std::vector<sf::CircleShape*> getAllHitboxes();

	void toControl() override;
	float getRotation() override;
	sf::Vector2f getPosition() override;
	void draw() override; 
	void drawShadow();

	void setPhycics(Car *car);
	void move(const sf::Vector2f &offset);
	void moveHitboxes(const sf::Vector2f &offset);
	void rorateHitboxes(const double &angle);
	void rotate(const double &angle);
	void updatePosition();

private:
	sf::RenderWindow *window;

	carType::Type *type;
	unsigned *weight;

	sf::Sprite *sprite;
	sf::Sprite *shadow;

	Door *door;

	Tire *tire;

	carPhysics *physics;

	bool isCollision[9];

	void gas(const sf::Keyboard::Key &key);
	void brake(const sf::Keyboard::Key &key);
	void handBrake(const sf::Keyboard::Key &key);
	void turnLeft(const sf::Keyboard::Key &key);
	void turnRight(const sf::Keyboard::Key &key);
};