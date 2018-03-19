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

	bool &getStateKeyGas();
	bool &getStateKeyBrake();
	bool &getStateKeyLeftTurn();
	bool &getStateKeyRightTurn();

protected:

	sf::Sprite *sprite;
	Car *car;

	int hp, armor, condition;

	bool stateKeyGas; // true - pressed , false - realsed
	bool stateKeyBrake; // -||-
	bool stateKeyLeftTurn;
	bool stateKeyRightTurn;

	virtual void controlBody() = 0;
	virtual void controlCar() = 0;

private:


};