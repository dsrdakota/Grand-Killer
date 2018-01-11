#include "TaxiTrailer.hpp"
#include "../../../../../../Manager/Texture.hpp"
#include <cmath>

TaxiTrailer::TaxiTrailer()
{
	sprite = new sf::Sprite(*textureManager::load("taxi", "data/Trailer/Part3/Textures/taxi.png"));

	sprite->setOrigin(106, 115);

	sprite->setPosition(sf::Vector2f(1172, 146));

	actualSpeed = new float(3);

	MAX_SPEED = new const float(5);

	door = new DoorTrailer;

	door->door->setOrigin(sprite->getOrigin().x - 68, sprite->getOrigin().y - 115);
	door->door->setPosition(sprite->getPosition());

	sprite->rotate(-141);
	door->door->setRotation(sprite->getRotation());

	door->center->setOrigin(door->door->getOrigin());
	door->center->setPosition(door->door->getPosition());
	door->center->setRotation(door->door->getRotation());
}

TaxiTrailer::~TaxiTrailer()
{
	textureManager::unload("taxi");

	delete sprite;

	delete actualSpeed;
	delete MAX_SPEED;
}  

void TaxiTrailer::Move(const sf::Vector2f & offset)
{
	sprite->move(offset);
	door->door->move(offset);
}

void TaxiTrailer::Rotate(const float &angle)
{
	sprite->rotate(angle);
	door->door->rotate(angle);
}

void TaxiTrailer::updatePosition()
{
	door->door->setOrigin(sprite->getOrigin().x - 68, sprite->getOrigin().y - 115);
	door->door->setPosition(sprite->getPosition());

	door->door->setRotation(sprite->getRotation());

	door->center->setOrigin(door->door->getOrigin());
	door->center->setPosition(door->door->getPosition());
	door->center->setRotation(door->door->getRotation());
}

void TaxiTrailer::boostSpeed()
{
	if (*actualSpeed != 3)
	{
		const float boostValue = 0.21f;

		if (*actualSpeed + boostValue <= *MAX_SPEED)
			*actualSpeed += boostValue;
		else
			*actualSpeed = *MAX_SPEED;
	}
}
