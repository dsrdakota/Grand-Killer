#include "Car.hpp"

#include "Behaviors/ToTurn.hpp"

#include "../Engine/Engine.hpp"

#include <iostream>

Car::Car() 
{ 
	sprite = new sf::Sprite();
	shadow = new sf::Sprite();

	weight = new unsigned;
	damageCondition = new int;
}

Car::~Car()
{
	delete sprite;
	delete door;
	delete tire;
	delete weight;
}

Movement * Car::getMovementClass()
{
	return movement;
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

Hitbox * Car::getHitboxClass()
{
	return hitbox;
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
		sf::Vector2f(boundingBox.width + 10.f, boundingBox.height + 10.f));
}
const unsigned& Car::getWeight()
{
	return *weight;
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

void Car::control()
{
	if (!driver)
		noneDriver();
}

void Car::move(const sf::Vector2f &offset)
{
	sprite->move(offset);
	shadow->move(offset);
	tire->move(offset);
	door->move(offset);
}

void Car::rotate(const float & angle)
{
	sprite->rotate(angle);
	shadow->rotate(angle);
	tire->rotate(angle);
	door->rotate(angle);
}

void Car::setAttributes()
{
	door = new Door(this);
	tire = new Tire(this);
	hitbox = new Hitbox(this);

	movement = new Movement(this);
	toTurn = new ToTurn(this);
}

void Car::noneDriver()
{
	movement->slack();
	toTurn->updatePosition();
}

void Car::draw()
{
	hitbox->update();

	if (!Camera::isOutsideView(shadow->getGlobalBounds()) &&
		!Camera::isOutsideView(sprite->getGlobalBounds()))
	{
		door->drawCenter();

		Painter::Instance().addToDraw(sprite);

		door->drawDoors();

		hitbox->draw();
	}
}

void Car::drawShadow()
{
	if (!Camera::isOutsideView(shadow->getGlobalBounds()) &&
		!Camera::isOutsideView(sprite->getGlobalBounds()))
	{
		Painter::Instance().addToDraw(shadow);
		tire->draw();
	}
}
