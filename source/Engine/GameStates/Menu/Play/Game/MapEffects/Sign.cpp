#include "Sign.hpp"

#include "../../../../../../Manager/Texture.hpp"

Sign::Sign(const sf::Vector2f &startPos, const float &rotation)
{
	state = drawState::On;
	this->startPos = startPos;
	startRotation = rotation;

	sign = new sf::Sprite(*textureManager::get("sign"));
	hitbox = new sf::CircleShape(5);

	sign->setOrigin(30, 72);
	hitbox->setOrigin(sign->getOrigin().x - 33,sign->getOrigin().y-60);
	
	sign->setPosition(startPos);
	hitbox->setPosition(startPos);

	hitbox->rotate(rotation);
	sign->rotate(rotation);
}

Sign::~Sign()
{
	delete sign;
	delete hitbox;
}

void Sign::setPosition(const sf::Vector2f & startPos, const float & rotation)
{
	sign->setPosition(startPos);
	hitbox->setPosition(startPos);

	hitbox->rotate(rotation);
	sign->rotate(rotation);
}

sf::Sprite * Sign::getSignSprite()
{
	return sign;
}

sf::CircleShape * Sign::getSignHitbox()
{
	return hitbox;
}

int Sign::getDrawState()
{
	return static_cast<int>(state);
}
