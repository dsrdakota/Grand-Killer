#include "Ambulance.hpp"

Ambulance::Ambulance(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Ambulance";
	sprite = new sf::Sprite(*TextureManager::get("Ambulance"));
	sprite->setPosition(startPos);
	sprite->setOrigin(39, 107);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("Ambulance_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(79, 122);

	countDoors = 2;
	*weight = 3200;

	setAttributes();
}
