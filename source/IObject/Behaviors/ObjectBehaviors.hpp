#pragma once

#include <SFML/Graphics.hpp>

class Car;

class ObjectBehaviors
{
public:

	void control();

	void getInCar(Car *car);
	void getOutOfCar();

	bool &getStateKeyGas();
	bool &getStateKeyBrake();
	bool &getStateKeyLeftTurn();
	bool &getStateKeyRightTurn();

protected:

	sf::Sprite *sprite;
	Car *car;

	bool stateKeyGas; // true - pressed , false - realsed
	bool stateKeyBrake; // -||-
	bool stateKeyLeftTurn;
	bool stateKeyRightTurn;

	virtual void controlBody() = 0;
	virtual void controlCar() = 0;
	virtual void showCarName() = 0;
};