#pragma once

#include <SFML/Graphics.hpp>

#include "Behaviors/ObjectBehaviors.hpp"

class Car;

class IObject
{
public:

	Car* getCar();

	void getInCar(Car *car);
	void getOutOfCar();

	virtual ObjectBehaviors *getBehaviors() = 0;

	const sf::Vector2f& getPosition();
	const float getRotation();

	void setHP(const int &hp);
	const int &getHP() const;

protected:

	sf::Sprite *sprite;
	Car *car;

	int hp, armor, condition;

private:


};