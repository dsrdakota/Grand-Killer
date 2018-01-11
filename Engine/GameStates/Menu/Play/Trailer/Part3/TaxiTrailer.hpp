#pragma once
#include <SFML/Graphics.hpp>
#include "DoorTrailer.hpp"
class TaxiTrailer
{
public:

	float *actualSpeed;
	const float *MAX_SPEED;

	sf::Sprite *sprite;

	DoorTrailer *door;

	TaxiTrailer();
	~TaxiTrailer();

	void Move(const sf::Vector2f &offset);
	void Rotate(const float &angle);
	void updatePosition();
	void boostSpeed();

};