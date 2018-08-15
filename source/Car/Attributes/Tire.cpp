#include "Tire.hpp"

#include "../Car.hpp"

#include "../../Engine/Engine.hpp"

#include <iostream>

Tire::Tire(Car *car)
{
	this->car = car;
	countTires = car->getCountTires();

	tires = new sf::RectangleShape[countTires];
	tiresPos = new sf::CircleShape[countTires];

	textureIndex = 1;

	sf::CircleShape shape(3);
	shape.setOrigin(3, 3);
	std::fill(tiresPos, tiresPos + countTires, shape);

	for (size_t i = 0;i < countTires;++i)
	{
		tires[i].setSize(sf::Vector2f(11, 28));
		tires[i].setTexture(TextureManager::get(car->getName() + "tire1"));
		tires[i].setRotation(car->getSprite()->getRotation());
	}

	//traces = new Traces(car, tiresPos);
}

Tire::~Tire()
{
	delete[]tires;
	delete[]tiresPos;
}

void Tire::updatePosition()
{
	if (static_cast<int>(*car->getMovementClass()->getSpeed()) * 20 / static_cast<int>(*car->getMovementClass()->getMaxSpeed()) < 20)
		textureIndex = static_cast<int>(*car->getMovementClass()->getSpeed()) * 20 / static_cast<int>(*car->getMovementClass()->getMaxSpeed());
	else
	{
		if (clock.time->asSeconds() > 0.15f)
		{
			textureIndex++;
			clock.clock->restart();
			*clock.time = sf::Time::Zero;
		}
	}

	if (textureIndex >= 20)
		textureIndex = 14;

	for (size_t i = 0; i < countTires; ++i)
	{
		tiresPos[i].setPosition(car->getSprite()->getPosition());
		tiresPos[i].setRotation(car->getSprite()->getRotation());

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);

		tires[i].setTexture(TextureManager::get(car->getName() + "tire" + std::to_string(textureIndex + 1)));
	}
}

void Tire::move(const sf::Vector2f & offset)
{
	for (size_t i = 0;i < countTires;++i)
	{
		tires[i].move(offset);
		tiresPos[i].move(offset);
	}
}

void Tire::rotate(const double & angle)
{
	for (size_t i = 0;i < countTires;++i)
	{
		tires[i].rotate(static_cast<float>(angle));
		tiresPos[i].rotate(static_cast<float>(angle));

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
	}
}

void Tire::setTraces()
{
	//traces->setTraces();
}

void Tire::draw()
{
	for (size_t i = 0;i < countTires;++i)
		Painter::Instance().addToDraw(tires + i);
}
