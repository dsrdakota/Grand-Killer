#include "Mini_truck.hpp"

Mini_truck::Mini_truck(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Mini truck";
	sprite = new sf::Sprite(*TextureManager::get("mini_truck"));
	sprite->setPosition(startPos);
	sprite->setOrigin(54, 116);
	sprite->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("mini_truck_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(79, 122);
	shadow->setRotation(startRot);

	countTires = 4;
	countDoors = 2;
	*weight = 3000;

	setAttributes();
	setDoorPosition();
	setTirePosition();
}

void Mini_truck::setDoorPosition()
{
	this->getDoorClass()->getUnderDoors()->setSize(sf::Vector2f(82, 100));
	this->getDoorClass()->getUnderDoors()->setOrigin(sprite->getOrigin().x - 13, sprite->getOrigin().y - 40);

	this->getDoorClass()->getDoorsHitbox()[0].setOrigin(sprite->getOrigin().x - 19.5f, sprite->getOrigin().y - 83);
	this->getDoorClass()->getDoorsHitbox()[1].setOrigin(sprite->getOrigin().x - 83.5f, sprite->getOrigin().y - 81);

	this->getDoorClass()->getDoors()[0].setSize(sf::Vector2f(10.f, 43));
	this->getDoorClass()->getDoors()[1].setSize(sf::Vector2f(10.f, 43));

	this->getDoorClass()->getDoors()[0].setOrigin(3, 3);
	this->getDoorClass()->getDoors()[1].setOrigin(1, 1);

	this->getDoorClass()->updatePosition();
}

void Mini_truck::setTirePosition()
{
	for (auto i = 0; i < 4; ++i)
		this->getTireClass()->getTires(i)->setOrigin(5, 12);

	this->getTireClass()->getTiresPos(0)->setOrigin(this->getSprite()->getOrigin().x - 10, this->getSprite()->getOrigin().y - 60);
	this->getTireClass()->getTiresPos(1)->setOrigin(this->getSprite()->getOrigin().x - 95.f, this->getSprite()->getOrigin().y - 60);

	this->getTireClass()->getTiresPos(2)->setOrigin(this->getTireClass()->getTiresPos(0)->getOrigin().x, this->getSprite()->getOrigin().y - 180);
	this->getTireClass()->getTiresPos(3)->setOrigin(this->getTireClass()->getTiresPos(1)->getOrigin().x, this->getSprite()->getOrigin().y - 180);

	this->getTireClass()->updatePosition();
}
