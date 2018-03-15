#include "Black_viper.hpp"

Black_viper::Black_viper(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Black_viper";
	sprite = new sf::Sprite(*TextureManager::get("Black_viper"));
	sprite->setPosition(startPos);
	sprite->setOrigin(44, 111);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("Black_viper_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(79, 128);

	countDoors = 2;
	*weight = 1750;

	setAttributes();
}
