#include "Taxi.hpp"

Taxi::Taxi(const sf::Vector2f &startPos, const float &startRot)
{
	name = "Taxi";
	sprite->setTexture(*TextureManager::get("taxi"));
	sprite->setPosition(startPos);
	sprite->setOrigin(41,99);
	sprite->setRotation(startRot);

	shadow->setTexture(*TextureManager::get("taxi_shadow"));
	shadow->setPosition(startPos.x + 20, startPos.y);
	shadow->setOrigin(81, 129);
	shadow->setRotation(startRot);

	countTires = 4;
	countDoors = 4;
	*weight = 2000;

	setAttributes();
	setDoorPosition();
	setTirePosition();
}

void Taxi::setDoorPosition()
{
	this->getDoorClass()->getUnderDoors()->setSize(sf::Vector2f(78, 120));
	this->getDoorClass()->getUnderDoors()->setOrigin(sprite->getOrigin().x - 2, sprite->getOrigin().y - 35);

	this->getDoorClass()->getDoorsHitbox()[0].setOrigin(sprite->getOrigin().x - 3, sprite->getOrigin().y - 62);
	this->getDoorClass()->getDoorsHitbox()[2].setOrigin(sprite->getOrigin().x - 3, sprite->getOrigin().y - 107);
	this->getDoorClass()->getDoorsHitbox()[1].setOrigin(sprite->getOrigin().x - 77, sprite->getOrigin().y - 59);
	this->getDoorClass()->getDoorsHitbox()[3].setOrigin(sprite->getOrigin().x - 77, sprite->getOrigin().y - 108);

	this->getDoorClass()->getDoors()[0].setSize(sf::Vector2f(9, 44));
	this->getDoorClass()->getDoors()[2].setSize(sf::Vector2f(8, 49));
	this->getDoorClass()->getDoors()[1].setSize(sf::Vector2f(8, 49));
	this->getDoorClass()->getDoors()[3].setSize(sf::Vector2f(7, 41));

	this->getDoorClass()->getDoors()[0].setOrigin(1, 1);
	this->getDoorClass()->getDoors()[2].setOrigin(1, 1);
	this->getDoorClass()->getDoors()[1].setOrigin(6, 0);
	this->getDoorClass()->getDoors()[3].setOrigin(6, 0);

	this->getDoorClass()->updatePosition();
}

void Taxi::setTirePosition()
{
	for (auto i = 0; i < 4; ++i)
		this->getTireClass()->getTires(i)->setOrigin(5, 12);

	this->getTireClass()->getTiresPos(0)->setOrigin(this->getSprite()->getOrigin().x, this->getSprite()->getOrigin().y - 30);
	this->getTireClass()->getTiresPos(1)->setOrigin(this->getSprite()->getOrigin().x - 75.f, this->getSprite()->getOrigin().y - 30);

	this->getTireClass()->getTiresPos(2)->setOrigin(this->getTireClass()->getTiresPos(0)->getOrigin().x, this->getSprite()->getOrigin().y - 140);
	this->getTireClass()->getTiresPos(3)->setOrigin(this->getTireClass()->getTiresPos(1)->getOrigin().x, this->getSprite()->getOrigin().y - 140);

	this->getTireClass()->updatePosition();
}
