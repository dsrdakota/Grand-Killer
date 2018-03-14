#include "Tire.hpp"

#include "../Car.hpp"

#include "../../Engine/Engine.hpp"

Tire::Tire(Car *car)
{
	tires = new sf::Sprite[4];
	tiresPos = new sf::CircleShape[4];

	sf::CircleShape shape(3);
	shape.setOrigin(3, 3);
	std::fill(tiresPos, tiresPos + 4, shape);

	for (auto i = 0;i < 4;++i)
	{
		tires[i].setTexture(*TextureManager::get(car->getName() + "tire"));
		tires[i].setRotation(car->getSprite()->getRotation());
	}

	for (auto i = 0;i < 4;++i)
	{
		tiresPos[i].setPosition(car->getSprite()->getPosition());
		tiresPos[i].setRotation(car->getSprite()->getRotation());

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
	}

	traces = new Traces(car, tiresPos);
}

Tire::~Tire()
{
	delete[]tires;
	delete[]tiresPos;
}

void Tire::move(const sf::Vector2f & offset)
{
	for (int i = 0;i < 4;++i)
	{
		tires[i].move(offset);
		tiresPos[i].move(offset);
	}
}

void Tire::rotate(const double & angle)
{
	for (int i = 0;i < 4;++i)
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
	for (auto i = 0;i < 4;++i)
		Painter::Instance().addToDraw(tires + i);
}
