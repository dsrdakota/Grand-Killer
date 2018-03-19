#include "Tire.hpp"

#include "../Car.hpp"

#include "../../Engine/Engine.hpp"

Tire::Tire(Car *car)
{
	this->car = car;
	countTires = car->getCountTires();

	tires = new sf::Sprite[countTires];
	tiresPos = new sf::CircleShape[countTires];

	sf::CircleShape shape(3);
	shape.setOrigin(3, 3);
	std::fill(tiresPos, tiresPos + countTires, shape);

	for (size_t i = 0;i < countTires;++i)
	{
		tires[i].setTexture(*TextureManager::get(car->getName() + "_tire"));
		tires[i].setRotation(car->getSprite()->getRotation());
	}

	traces = new Traces(car, tiresPos);
}

Tire::~Tire()
{
	delete[]tires;
	delete[]tiresPos;
}

void Tire::updatePosition()
{
	for (size_t i = 0; i < countTires; ++i)
	{
		tiresPos[i].setPosition(car->getSprite()->getPosition());
		tiresPos[i].setRotation(car->getSprite()->getRotation());

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
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
	traces->setTraces();
}

void Tire::draw()
{
	for (size_t i = 0;i < countTires;++i)
		Painter::Instance().addToDraw(tires + i);
}
