#pragma once

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

#include "Attributes/Door.hpp"
#include "Attributes/Tire.hpp"
#include "Attributes/Hitbox.hpp"

#include "Behaviors/Movement.hpp"
#include "Behaviors/ToTurn.hpp"
#include "Behaviors/Slide.hpp"
#include "Behaviors/Traces.hpp"

class Car 
{
public: 

	Movement* getMovementClass();
	ToTurn* getToTurnClass();
	Door* getDoorClass();
	Tire* getTireClass();
	Hitbox* getHitboxClass();

	const std::string& getName();
	const sf::Sprite* getSprite();

	const sf::FloatRect getGlobalBounds();

	const unsigned &getWeight();
	
	void setDamageCondition(const int &newDamageCondition);
	const int *getDamageCondition();

	const unsigned &getCountDoors();
	const unsigned &getCountTires();

	void setDriver(IObject *driver);
	IObject* getDriver();

	void control();
	void move(const sf::Vector2f &offset);
	void rotate(const float &angle);

	void draw();
	void drawShadow();

protected:

	IObject *driver;

	Movement *movement;
	ToTurn *toTurn;

	Door *door;
	Tire *tire;
	Hitbox *hitbox;

	unsigned *weight;
	int *damageCondition;

	unsigned countDoors;
	unsigned countTires;

	sf::Sprite *sprite;
	sf::Sprite *shadow;

	std::string name;

	Car();
	~Car();

	void setAttributes();
	void noneDriver();
};