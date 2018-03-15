#pragma once

#include <SFML/Graphics.hpp>

class Car;

class IObject
{
public:

	void control();

	void getInCar(Car *car);
	void getOutOfCar();

	const sf::Vector2f& getPosition();
	const float getRotation();

protected:

	sf::Sprite *sprite;
	Car *car;

	int hp, armor, condition;

	virtual void controlBody() = 0;
	virtual void controlCar() = 0;

private:


};