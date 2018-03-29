#include "Dodge.hpp"

Dodge::Dodge(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Dodge";
	sprite = new sf::Sprite(*TextureManager::get("dodge"));
	sprite->setPosition(startPos);
	sprite->setOrigin(42, 105);
	sprite->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("dodge_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(77, 122);
	shadow->setRotation(startRot);

	countTires = 4;
	countDoors = 4;
	*weight = 2200;

	setAttributes();
	setDoorPosition();
	setTirePosition();
}

void Dodge::setDoorPosition()
{
	this->getDoorClass()->getUnderDoors()->setSize(sf::Vector2f(81, 130));
	this->getDoorClass()->getUnderDoors()->setOrigin(sprite->getOrigin().x - 2, sprite->getOrigin().y - 40);

	this->getDoorClass()->getDoorsHitbox()[0].setOrigin(sprite->getOrigin().x - 6.f, sprite->getOrigin().y - 75);
	this->getDoorClass()->getDoorsHitbox()[2].setOrigin(sprite->getOrigin().x - 4.5f, sprite->getOrigin().y - 112.5f);
	this->getDoorClass()->getDoorsHitbox()[1].setOrigin(sprite->getOrigin().x - 76.5f, sprite->getOrigin().y - 66);
	this->getDoorClass()->getDoorsHitbox()[3].setOrigin(sprite->getOrigin().x - 74.5f, sprite->getOrigin().y - 113);

	this->getDoorClass()->getDoors()[0].setSize(sf::Vector2f(11.5f, 34));
	this->getDoorClass()->getDoors()[2].setSize(sf::Vector2f(12.f, 41));
	this->getDoorClass()->getDoors()[1].setSize(sf::Vector2f(10.5f, 45));
	this->getDoorClass()->getDoors()[3].setSize(sf::Vector2f(9.5f, 36.5f));

	this->getDoorClass()->getDoors()[0].setOrigin(3, 3);
	this->getDoorClass()->getDoors()[2].setOrigin(1, 1);
	this->getDoorClass()->getDoors()[1].setOrigin(5, 4);
	this->getDoorClass()->getDoors()[3].setOrigin(3, 1);

	this->getDoorClass()->updatePosition();
}

void Dodge::setTirePosition()
{
	for (auto i = 0; i < 4; ++i)
		this->getTireClass()->getTires(i)->setOrigin(5, 12);

	this->getTireClass()->getTiresPos(0)->setOrigin(this->getSprite()->getOrigin().x + 1, this->getSprite()->getOrigin().y - 40);
	this->getTireClass()->getTiresPos(1)->setOrigin(this->getSprite()->getOrigin().x - 80.f, this->getSprite()->getOrigin().y - 40);

	this->getTireClass()->getTiresPos(2)->setOrigin(this->getTireClass()->getTiresPos(0)->getOrigin().x, this->getSprite()->getOrigin().y - 165);
	this->getTireClass()->getTiresPos(3)->setOrigin(this->getTireClass()->getTiresPos(1)->getOrigin().x, this->getSprite()->getOrigin().y - 165);

	this->getTireClass()->updatePosition();
}
