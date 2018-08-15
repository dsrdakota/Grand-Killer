#pragma once

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

#include "Attributes/Door.hpp"
#include "Attributes/Tire.hpp"

#include "Behaviors/ToTurn.hpp"
#include "Behaviors/Slide.hpp"
#include "Behaviors/Traces.hpp"

class Car : public Moveable
{
public: 

	ToTurn* getToTurnClass();
	Door* getDoorClass();
	Tire* getTireClass();

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

	const sf::Vector2f getPosition() const override;
	const float getRotation() const override;

	void move(const sf::Vector2f& offset) const override;
	void rotate(const float &angle) const override;

	void control();

	void draw();
	void drawShadow();

protected:

	IObject *driver;

	ToTurn *toTurn;

	Door *door;
	Tire *tire;

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