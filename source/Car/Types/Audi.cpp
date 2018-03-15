#include "Audi.hpp"

Audi::Audi(const sf::Vector2f &startPos, const float &startRot) : Car::Car()
{
	name = "Audi";
	sprite->setTexture(*TextureManager::get("audi"));
	sprite->setPosition(startPos);
	sprite->setOrigin(48, 111);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow->setTexture(*TextureManager::get("audi_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(83, 128);

	countDoors = 4;
	*weight = 1500;

	setAttributes();
}