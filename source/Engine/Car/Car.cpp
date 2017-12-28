#include "Car.hpp"
#include "../../Manager/Texture.hpp"
#include "../../Manager/renderSprites.hpp"

#include "../carPhycics/carPhycics.hpp"

#include <iostream>
#include <string>
#include <fstream>

Car::Car(const carType::Type &type, const sf::Vector2f &startPos) : window(Game::Instance().getWindow())
{
	this->type = new carType::Type(type);
	shape = new Shape;

	std::string pathToShape = "data/Models/Cars/";
	std::string pathToTexture = pathToShape;
	std::string nameTexture;
	sf::Vector2f origin;

	switch (type)
	{
	case carType::Type::Ambulance:
		break;
	case carType::Type::Audi:
		break;
	case carType::Type::Black_viper:
		break;
	case carType::Type::Car:
		break;
	case carType::Type::Mini_truck:
		break;
	case carType::Type::Mini_van:
		break;
	case carType::Type::Police:
		break;
	case carType::Type::Taxi:

		weight = new unsigned(1500);

		origin = sf::Vector2f(105, 102);

		pathToShape += "Taxi/taxi.gk";
		pathToTexture += "Taxi/taxi.png";
		nameTexture = "Taxi";

		break;
	case carType::Type::Truck:
		break;
	}
	tire = new Tire(this,type);
	door = new Door(type);
	shape->setShape(pathToShape, pathToTexture, nameTexture);

	shape->setPosition(startPos);
	shape->setOrigin(origin);

	door->setPosition(shape->getShape(), type);
	tire->setPosition(shape->getShape(), type);

	phycics = new carPhycics(this);

	for (size_t i = 0;i < shape->getShape()->getPointCount();i++)
	{
		sf::CircleShape *buf = new sf::CircleShape(1);
		buf->setOrigin(shape->getShape()->getOrigin() - shape->getShape()->getPoint(i));
		buf->setFillColor(sf::Color::Red);

		buf->setPosition(shape->getShape()->getPosition());
		hitboxes.push_back(buf);
	}
}

Car::~Car()
{
	delete shape;
	delete door;
	delete weight;

	delete phycics; // kappa
}

std::vector<sf::CircleShape*> Car::getAllHitboxes()
{
	return hitboxes;
}

double Car::getSpeed()
{
	return *phycics->getPhycicsMove()->getSpeed();
}

void Car::setSpeed(const float &speed)
{
	phycics->getPhycicsMove()->setSpeed(speed);
}

sf::Vector2f Car::getMovementVector()
{
	return phycics->getPhycicsMove()->getMovementVector(shape->getShape()->getRotation() - static_cast<float>(*getOverSteerValue()));
}

const double Car::getMaxSpeed()
{
	return *phycics->getPhycicsMove()->getMaxSpeed();
}

const double * Car::getOverSteerValue()
{
	return phycics->getPhycicsTurn()->getOverSteerValue();
}

const int Car::getOverSteerSide()
{
	return phycics->getPhycicsTurn()->getSlidePhycics()->getOverSteerSide();
}

double * Car::getBreakingForceOfSlide()
{
	return phycics->getPhycicsTurn()->getSlidePhycics()->getBreakingForceOfSlide();
}

int Car::getTypeOfDrive()
{
	return phycics->getPhycicsMove()->getTypeOfDrive();
}

int Car::getStateMoving()
{
	return phycics->getPhycicsMove()->getStateMoving();
}

bool Car::isSlide()
{
	return phycics->getPhycicsTurn()->isSlide();
}

void Car::toControl()
{
	updatePosition();

	// ----- Main control

	turnLeft(sf::Keyboard::A);
	turnRight(sf::Keyboard::D);

	gas(sf::Keyboard::W);
	brake(sf::Keyboard::S);

	handBrake(sf::Keyboard::Space);

	// ----- Doors control

	openDoors(Door::Side::front_left,sf::Keyboard::U);

	closeDoors(Door::Side::front_left, sf::Keyboard::I);

	openDoors(Door::Side::front_right, sf::Keyboard::P);

	closeDoors(Door::Side::front_right, sf::Keyboard::O);

	openDoors(Door::Side::front_left, sf::Keyboard::U);

	closeDoors(Door::Side::front_left, sf::Keyboard::I);

	openDoors(Door::Side::front_right, sf::Keyboard::P);

	closeDoors(Door::Side::front_right, sf::Keyboard::O);

	openDoors(Door::Side::back_left, sf::Keyboard::H);

	closeDoors(Door::Side::back_left, sf::Keyboard::J);

	openDoors(Door::Side::back_right, sf::Keyboard::L);

	closeDoors(Door::Side::back_right, sf::Keyboard::K);

	// -----
}

void Car::setCamera()
{
	Map::Instance().updateView(shape->getShape()->getPosition());
}

void Car::setPhycics(Car *car)
{
	phycics = new carPhycics(car);
}

void Car::move(const sf::Vector2f & offset)
{
	shape->getShape()->move(offset);
	door->move(offset);
	tire->move(offset);
	phycics->move(offset);

	for (const auto &i : hitboxes)
		i->move(offset);
}

void Car::rotate(const double & angle)
{
	shape->getShape()->rotate(static_cast<float>(angle));
	door->rotate(static_cast<float>(angle));
	tire->rotate(angle, shape->getShape());

	for (const auto &i : hitboxes)
		i->rotate(static_cast<float>(angle));
}

void Car::updatePosition()
{
	phycics->updatePosition();
}

void Car::openDoors(const Door::Side &side, const sf::Keyboard::Key &key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		float *angle = nullptr;
		switch (side)
		{
		case Door::Side::front_left:
		case Door::Side::back_left:
			angle = new float(0.015f);
			break;

		case Door::Side::front_right:
		case Door::Side::back_right:
			angle = new float(-0.015f);
			break;
		}
		door->openDoor(door->getDoor(static_cast<int>(side)), angle, static_cast<int>(side));
	}
}

void Car::closeDoors(const Door::Side & side, const sf::Keyboard::Key &key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		float *angle = nullptr;
		switch (side)
		{
		case Door::Side::front_left:
		case Door::Side::back_left:
			angle = new float(-0.015f);
			break;

		case Door::Side::front_right:
		case Door::Side::back_right:
			angle = new float(0.015f);
			break;
		}
		door->closeDoor(door->getDoor(static_cast<int>(side)), angle, static_cast<int>(side));
	}
}

void Car::draw()
{
	tire->draw();

	door->drawCenter();

	renderSprites::Instance().addToRender(shape->getShape());

	door->drawDoors();

	phycics->draw();

	for(const auto &i:hitboxes)
		renderSprites::Instance().addToRender(i);

	//tire->draw();

}

void Car::gas(const sf::Keyboard::Key & key)
{
	phycics->boostSpeed(key);
}

void Car::brake(const sf::Keyboard::Key & key)
{
	phycics->reduceSpeed(key);
}

void Car::handBrake(const sf::Keyboard::Key & key)
{
	phycics->handBrake(key);
}

void Car::turnLeft(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key))
		phycics->turn(toTurn::Direction::Left);
	else
		*phycics->getPhycicsTurn()->getStatusKeyToTurn(toTurn::Direction::Left) = toTurn::keyStatus::Released;
}

void Car::turnRight(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key))
		phycics->turn(toTurn::Direction::Right);
	else
		*phycics->getPhycicsTurn()->getStatusKeyToTurn(toTurn::Direction::Right) = toTurn::keyStatus::Released;
}