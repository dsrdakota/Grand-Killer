#include "Police.hpp"

Police::Police(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Police";
	sprite = new sf::Sprite(*TextureManager::get("Police"));
	sprite->setPosition(startPos);
	sprite->setOrigin(45, 110);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("Police_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(80, 129);

	countDoors = 4;
	*weight = 1850;

	setAttributes();
}
