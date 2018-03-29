#include "Black_viper.hpp"

Black_viper::Black_viper(const sf::Vector2f & startPos, const float & startRot)
{
	name = "Black_viper";
	sprite = new sf::Sprite(*TextureManager::get("black_viper"));
	sprite->setPosition(startPos);
	sprite->setOrigin(44, 111);
	sprite->setRotation(startRot);

	shadow = new sf::Sprite(*TextureManager::get("black_viper_shadow"));
	shadow->setPosition(startPos.x + 40, startPos.y);
	shadow->setOrigin(79, 128);
	shadow->setRotation(startRot);

	countTires = 4;
	countDoors = 2;
	*weight = 1750;

	setAttributes();
	setDoorPosition();
	setTirePosition();
}

void Black_viper::setDoorPosition()
{
	this->getDoorClass()->getUnderDoors()->setSize(sf::Vector2f(82, 120));
	this->getDoorClass()->getUnderDoors()->setOrigin(sprite->getOrigin().x - 2, sprite->getOrigin().y - 35);

	this->getDoorClass()->getDoorsHitbox()[0].setOrigin(sprite->getOrigin().x - 6.f, sprite->getOrigin().y - 87);
	this->getDoorClass()->getDoorsHitbox()[1].setOrigin(sprite->getOrigin().x - 73.8f, sprite->getOrigin().y - 87);

	this->getDoorClass()->getDoors()[0].setSize(sf::Vector2f(9.8f, 50));
	this->getDoorClass()->getDoors()[1].setSize(sf::Vector2f(9.8f, 50));

	this->getDoorClass()->getDoors()[0].setOrigin(3, 3);
	this->getDoorClass()->getDoors()[1].setOrigin(1, 1);

	this->getDoorClass()->updatePosition();
}

void Black_viper::setTirePosition()
{
	for (auto i = 0; i < 4; ++i)
		this->getTireClass()->getTires(i)->setOrigin(5, 12);
		
	this->getTireClass()->getTiresPos(0)->setOrigin(this->getSprite()->getOrigin().x + 1.f, this->getSprite()->getOrigin().y - 50);
	this->getTireClass()->getTiresPos(1)->setOrigin(this->getSprite()->getOrigin().x - 81.f, this->getSprite()->getOrigin().y - 50);

	this->getTireClass()->getTiresPos(2)->setOrigin(this->getTireClass()->getTiresPos(0)->getOrigin().x - 2.f, this->getSprite()->getOrigin().y - 160);
	this->getTireClass()->getTiresPos(3)->setOrigin(this->getTireClass()->getTiresPos(1)->getOrigin().x + 1.f, this->getSprite()->getOrigin().y - 160);

	this->getTireClass()->updatePosition();
}
