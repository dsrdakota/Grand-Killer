#include "Taxi.hpp"

#include "../../Engine/Engine.hpp"

#include "../Attributes/Door.hpp"
#include "../Attributes/Tire.hpp"
#include "../Attributes/Hitbox.hpp"

#include "../Behaviors/Movement.hpp"
#include "../Behaviors/ToTurn.hpp"

Taxi::Taxi(const sf::Vector2f &startPos, const float &startRot) : Car::Car()
{
	name = "Taxi";
	sprite = new sf::Sprite(*TextureManager::get("Taxi"));
	sprite->setPosition(startPos);
	sprite->setOrigin(41,99);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("Taxi_shadow"));
	shadow->setPosition(startPos.x + 20, startPos.y);
	shadow->setOrigin(81, 129);

	*weight = 2000;

	setAttributes();
}
