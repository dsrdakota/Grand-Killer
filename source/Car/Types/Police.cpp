#include "Police.hpp"

Police::Police(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Police";
	sprite = new sf::Sprite(*TextureManager::get("police"));
	sprite->setPosition(startPos);
	sprite->setOrigin(45, 110);
	sprite->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("police_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(80, 129);
	shadow->setRotation(startRot);

	countTires = 4;
	countDoors = 4;
	*weight = 1850;

	setAttributes();
	setDoorPosition();
	setTirePosition();
}

void Police::setDoorPosition()
{
	this->getDoorClass()->getUnderDoors()->setSize(sf::Vector2f(78, 130));
	this->getDoorClass()->getUnderDoors()->setOrigin(sprite->getOrigin().x - 7, sprite->getOrigin().y - 40);

	this->getDoorClass()->getDoorsHitbox()[0].setOrigin(sprite->getOrigin().x - 9.3f, sprite->getOrigin().y - 73.5f);
	this->getDoorClass()->getDoorsHitbox()[2].setOrigin(sprite->getOrigin().x - 9.3f, sprite->getOrigin().y - 119);
	this->getDoorClass()->getDoorsHitbox()[1].setOrigin(sprite->getOrigin().x - 78.8f, sprite->getOrigin().y - 68.5f);
	this->getDoorClass()->getDoorsHitbox()[3].setOrigin(sprite->getOrigin().x - 79.3f, sprite->getOrigin().y - 119);

	this->getDoorClass()->getDoors()[0].setSize(sf::Vector2f(11.2f, 43));
	this->getDoorClass()->getDoors()[2].setSize(sf::Vector2f(10.2f, 54.5f));
	this->getDoorClass()->getDoors()[1].setSize(sf::Vector2f(10.7f, 49));
	this->getDoorClass()->getDoors()[3].setSize(sf::Vector2f(10.2f, 49));

	this->getDoorClass()->getDoors()[0].setOrigin(3, 3);
	this->getDoorClass()->getDoors()[2].setOrigin(1, 1);
	this->getDoorClass()->getDoors()[1].setOrigin(5, 4);
	this->getDoorClass()->getDoors()[3].setOrigin(6, 0);

	this->getDoorClass()->updatePosition();
}

void Police::setTirePosition()
{
	for (auto i = 0; i < 4; ++i)
		this->getTireClass()->getTires(i)->setOrigin(5, 12);

	this->getTireClass()->getTiresPos(0)->setOrigin(this->getSprite()->getOrigin().x + 1, this->getSprite()->getOrigin().y - 45);
	this->getTireClass()->getTiresPos(1)->setOrigin(this->getSprite()->getOrigin().x - 86.f, this->getSprite()->getOrigin().y - 45);

	this->getTireClass()->getTiresPos(2)->setOrigin(this->getTireClass()->getTiresPos(0)->getOrigin().x - 3, this->getSprite()->getOrigin().y - 170);
	this->getTireClass()->getTiresPos(3)->setOrigin(this->getTireClass()->getTiresPos(1)->getOrigin().x + 1, this->getSprite()->getOrigin().y - 170);

	this->getTireClass()->updatePosition();
}
