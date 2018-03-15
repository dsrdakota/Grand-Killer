#pragma once

#include <SFML/Graphics.hpp>

class Car;

class Door
{
public:

	enum class doorSide
	{
		leftFront,
		rightFront,
		leftBack,
		rightBack
	};

	Door(const sf::Sprite *sprite);
	~Door();

	void move(const sf::Vector2f &offset);
	void rotate(const float &angle);
	void setRotation(const float &rotation);

	void drawCenter();
	void drawDoors();

private:

	const sf::Sprite *sprite;

	sf::RectangleShape *doors;
	sf::Texture *doorTextures;
	sf::RectangleShape *underDoors;
	sf::CircleShape *doorsHitbox;

	unsigned countDoors;

	const float *MAX_ANGLEN_OPEN;
	float *angleOpen;

	void updatePosition();

	void open(const doorSide &side, const float &angle = 1);
	void close(const doorSide &side, const float &angle = -1);
};