#include "Dodge.hpp"

Dodge::Dodge(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Dodge";
	sprite = new sf::Sprite(*TextureManager::get("Dodge"));
	sprite->setPosition(startPos);
	sprite->setOrigin(42, 105);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("Dodge_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(77, 122);

	countDoors = 4;
	*weight = 2200;

	setAttributes();
}
