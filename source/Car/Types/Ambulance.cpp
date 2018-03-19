#include "Ambulance.hpp"

Ambulance::Ambulance(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Ambulance";
	sprite = new sf::Sprite(*TextureManager::get("ambulance"));
	sprite->setPosition(startPos);
	sprite->setOrigin(39, 107);
	sprite->setRotation(startRot);
	shadow->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("ambulance_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(79, 122);

	countTires = 4;
	countDoors = 2;
	*weight = 3200;

	setAttributes();
	setDoorPosition();
	setTirePosition();
}

void Ambulance::setDoorPosition()
{
	this->getDoorClass()->getUnderDoors()->setSize(sf::Vector2f(80, 100));
	this->getDoorClass()->getUnderDoors()->setOrigin(sprite->getOrigin().x - 1, sprite->getOrigin().y - 40);

	this->getDoorClass()->getDoorsHitbox()[0].setOrigin(sprite->getOrigin().x - 3.5f, sprite->getOrigin().y - 42);
	this->getDoorClass()->getDoorsHitbox()[1].setOrigin(sprite->getOrigin().x - 74.5f, sprite->getOrigin().y - 40);

	this->getDoorClass()->getDoors()[0].setSize(sf::Vector2f(7.f, 34));
	this->getDoorClass()->getDoors()[1].setSize(sf::Vector2f(7.f, 34));

	this->getDoorClass()->getDoors()[0].setOrigin(3, 3);
	this->getDoorClass()->getDoors()[1].setOrigin(1, 1);

	this->getDoorClass()->updatePosition();
}

void Ambulance::setTirePosition()
{
	for (auto i = 0; i < 4; ++i)
		this->getTireClass()->getTires(i)->setOrigin(5, 12);

	this->getTireClass()->getTiresPos(0)->setOrigin(this->getSprite()->getOrigin().x, this->getSprite()->getOrigin().y - 37);
	this->getTireClass()->getTiresPos(1)->setOrigin(this->getSprite()->getOrigin().x - 75.f, this->getSprite()->getOrigin().y - 37);

	this->getTireClass()->getTiresPos(2)->setOrigin(this->getTireClass()->getTiresPos(0)->getOrigin().x, this->getSprite()->getOrigin().y - 170);
	this->getTireClass()->getTiresPos(3)->setOrigin(this->getTireClass()->getTiresPos(1)->getOrigin().x, this->getSprite()->getOrigin().y - 170);

	this->getTireClass()->updatePosition();
}
