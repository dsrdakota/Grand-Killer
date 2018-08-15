#include "Car.hpp"

#include "Behaviors/ToTurn.hpp"

#include "../Engine/Engine.hpp"

Car::Car() 
{ 
	sprite = new sf::Sprite();
	shadow = new sf::Sprite();

	weight = new unsigned;
	damageCondition = new int(100);
}

Car::~Car()
{
	delete sprite;
	delete door;
	delete tire;
	delete weight;
}

ToTurn * Car::getToTurnClass()
{
	return toTurn;
}

Door * Car::getDoorClass()
{
	return door;
}

Tire * Car::getTireClass()
{
	return tire;
}

const std::string & Car::getName()
{
	return name;
}

const sf::Sprite* Car::getSprite()
{
	return sprite;
}

const sf::FloatRect Car::getGlobalBounds()
{
	const auto &boundingBox = sprite->getGlobalBounds();
	return sf::FloatRect(sf::Vector2f(boundingBox.left - 10.f, boundingBox.top - 10.f),
		sf::Vector2f(boundingBox.width + 20.f, boundingBox.height + 20.f));
}
const unsigned& Car::getWeight()
{
	return *weight;
}

void Car::setDamageCondition(const int & newDamageCondition)
{
	if (newDamageCondition < 0)
		this->damageCondition = 0;
	else if (newDamageCondition <= 100)
		*this->damageCondition = newDamageCondition;
}

const int * Car::getDamageCondition()
{
	return damageCondition;
}

const unsigned & Car::getCountDoors()
{
	return countDoors;
}

const unsigned & Car::getCountTires()
{
	return countTires;
}

void Car::setDriver(IObject * driver)
{
	this->driver = driver;
}

IObject * Car::getDriver()
{
	return driver;
}

const sf::Vector2f Car::getPosition() const
{
	return sprite->getPosition();
}

const float Car::getRotation() const
{
	return sprite->getRotation();
}

void Car::move(const sf::Vector2f & offset) const
{
	sprite->move(offset);
	shadow->move(offset);
	tire->move(offset);
	door->move(offset);
}

void Car::rotate(const float & angle) const
{
	sprite->rotate(angle);
	shadow->rotate(angle);
	tire->rotate(angle);
	door->rotate(angle);
}

void Car::control()
{
	if (!driver)
		noneDriver();
}

void Car::setAttributes()
{
	MAX_SPEED = CarConfig::getValue(name, "MAX_SPEED");
	acceleration = CarConfig::getValue(name, "acceleration");
	breakingForce = CarConfig::getValue(name, "breakingForce");

	door = new Door(this);
	tire = new Tire(this);

	toTurn = new ToTurn(this);
}

void Car::noneDriver()
{
	slack();
	toTurn->updatePosition();
}

void Car::draw()
{
	if (!Camera::isOutsideView(shadow->getGlobalBounds()) &&
		!Camera::isOutsideView(this->getGlobalBounds()))
	{
		door->drawCenter();

		Painter::Instance().addToDraw(sprite);

		door->drawDoors();
	}
}

void Car::drawShadow()
{
	if (!Camera::isOutsideView(shadow->getGlobalBounds()) &&
		!Camera::isOutsideView(this->getGlobalBounds()))
	{
		Painter::Instance().addToDraw(shadow);
		tire->draw();
	}
}
