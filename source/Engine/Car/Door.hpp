#pragma once

#include <SFML/Graphics.hpp>
#include "carType.hpp"

class Door
{
public:

	enum class doorSide
	{
		leftFront,
		leftBack,
		rightFront,
		rightBack
	};

	Door(const sf::Sprite *sprite, const carType::Type &type);
	~Door();

	void toControl();
	void move(const sf::Vector2f &offset);
	void rotate(const float &angle);
	void setRotation(const float &rotation);

	void drawCenter();
	void drawDoors();

private:

	const sf::Sprite *car;

	sf::RectangleShape *doors;
	sf::Texture *doorTextures;
	sf::RectangleShape *underDoors;
	sf::CircleShape *doorsHitbox;

	const float *MAX_ANGLEN_OPEN;
	float *angleOpen;

	void updatePosition();

	void open(const doorSide &side, const float &angle = 1);
	void close(const doorSide &side, const float &angle = -1);
};