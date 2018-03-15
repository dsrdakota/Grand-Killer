#include "Mini_truck.hpp"

Mini_truck::Mini_truck(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Mini_truck";
	sprite = new sf::Sprite(*TextureManager::get("Mini_truck"));
	sprite->setPosition(startPos);
	sprite->setOrigin(54, 116);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("Mini_truck_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(79, 122);

	countDoors = 2;
	*weight = 3000;

	setAttributes();
}
