#include "Audi.hpp"

Audi::Audi(const sf::Vector2f &startPos, const float &startRot)
{
	name = "Audi";
	sprite->setTexture(*TextureManager::get("audi"));
	sprite->setPosition(startPos);
	sprite->setOrigin(48, 111);
	sprite->setRotation(startRot);

	shadow->setTexture(*TextureManager::get("audi_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(83, 128);
	shadow->setRotation(startRot);

	countTires = 4;
	countDoors = 4;
	*weight = 1500;

	setAttributes();
	setDoorPosition();
	setTirePosition();
}

void Audi::setDoorPosition()
{
	this->getDoorClass()->getUnderDoors()->setSize(sf::Vector2f(78, 130));
	this->getDoorClass()->getUnderDoors()->setOrigin(sprite->getOrigin().x - 10, sprite->getOrigin().y - 40);

	this->getDoorClass()->getDoorsHitbox()[0].setOrigin(sprite->getOrigin().x - 12.5f, sprite->getOrigin().y - 70.5f);
	this->getDoorClass()->getDoorsHitbox()[2].setOrigin(sprite->getOrigin().x - 12, sprite->getOrigin().y - 122);
	this->getDoorClass()->getDoorsHitbox()[1].setOrigin(sprite->getOrigin().x - 80.5f, sprite->getOrigin().y - 68.5f);
	this->getDoorClass()->getDoorsHitbox()[3].setOrigin(sprite->getOrigin().x - 80.5f, sprite->getOrigin().y - 122);

	this->getDoorClass()->getDoors()[0].setSize(sf::Vector2f(10.5f, 49));
	this->getDoorClass()->getDoors()[2].setSize(sf::Vector2f(10, 53));
	this->getDoorClass()->getDoors()[1].setSize(sf::Vector2f(10.5f, 52));
	this->getDoorClass()->getDoors()[3].setSize(sf::Vector2f(10, 49));

	this->getDoorClass()->getDoors()[0].setOrigin(3, 3);
	this->getDoorClass()->getDoors()[2].setOrigin(1, 1);
	this->getDoorClass()->getDoors()[1].setOrigin(5, 4);
	this->getDoorClass()->getDoors()[3].setOrigin(6, 0);

	this->getDoorClass()->updatePosition();
}

void Audi::setTirePosition()
{
	for (auto i = 0; i < 4; ++i)
		this->getTireClass()->getTires(i)->setOrigin(5, 12);

	this->getTireClass()->getTiresPos(0)->setOrigin(this->getSprite()->getOrigin().x, this->getSprite()->getOrigin().y - 45);
	this->getTireClass()->getTiresPos(1)->setOrigin(this->getSprite()->getOrigin().x - 89.f, this->getSprite()->getOrigin().y - 45);

	this->getTireClass()->getTiresPos(2)->setOrigin(this->getTireClass()->getTiresPos(0)->getOrigin().x - 4.f, this->getSprite()->getOrigin().y - 170);
	this->getTireClass()->getTiresPos(3)->setOrigin(this->getTireClass()->getTiresPos(1)->getOrigin().x + 2.f, this->getSprite()->getOrigin().y - 170);

	this->getTireClass()->updatePosition();
}
