#include "Light.hpp"

#include "../../../../../../Manager/Texture.hpp"
#include "../mGame.hpp"

Light::Light(const sf::Vector2f & startPos, const float & rotation)
{
	state = drawState::On;
	startPosition = startPos;
	startRotation = rotation;
	
	stake = new sf::Sprite(*textureManager::get("stake"));
	light = new sf::Sprite(*textureManager::get("light1"));
	hitboxLight = new sf::CircleShape(5);

	stake->setOrigin(123, 53);
	light->setOrigin(stake->getOrigin().x - 15, stake->getOrigin().y + 2);
	hitboxLight->setOrigin(stake->getOrigin().x - 119, stake->getOrigin().y - 50);

	stake->setPosition(startPos);
	light->setPosition(startPos);
	hitboxLight->setPosition(startPos);

	stake->setRotation(rotation);
	hitboxLight->setRotation(rotation);
	light->setRotation(rotation);

	animation = false;
	speedAnimation = 0;
	moveOffset = sf::Vector2f(0, 0);
	timeOfAnimation = 6;
}

Light::~Light()
{
	delete light;
	delete hitboxLight;
}

void Light::setPosition(const sf::Vector2f & startPos, const float & rotation)
{
	stake->setPosition(startPos);
	light->setPosition(startPos);
	hitboxLight->setPosition(startPos);

	stake->setRotation(rotation);
	hitboxLight->setRotation(rotation);
	light->setRotation(rotation);

	startPosition = startPos;
	startRotation = rotation;
}

sf::Sprite * Light::getStakeSprite()
{
	return stake;
}

sf::Sprite * Light::getLightSprite()
{
	return light;
}

sf::CircleShape * Light::getLightHitbox()
{
	return hitboxLight;
}

int Light::getDrawState()
{
	return static_cast<int>(state);
}

void Light::checkCollision()
{
}

void Light::playAnimation()
{
}
