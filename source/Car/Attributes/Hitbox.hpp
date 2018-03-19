#pragma once

#include <SFML/Graphics.hpp>

class Car;

class Hitbox
{
public:

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

	Hitbox(Car *car);
	~Hitbox();

	bool &getBoolIsCollision(const collisionSide &side);

	std::vector<sf::CircleShape*> getCollisionHitbox(const hitboxPosition &pos);
	collisionSide *getLastCollisionSide();
	const std::vector<sf::CircleShape*> getAllHitboxes();

	void moveHitboxes(const sf::Vector2f &offset);
	void rotateHitboxes(const double &angle);
	static void rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle);
	static void moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset);

	static sf::Vector2f getCenterOfHitbox(const sf::CircleShape & hitbox);

	void update();
	void draw();

private:

	const sf::Sprite *sprite;

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

	bool isCollision[9];
	collisionSide lastCollisionSide;
};