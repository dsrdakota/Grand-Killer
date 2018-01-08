#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Car/Car.hpp"
#include <memory>

class carDentHitbox
{
public:

	carDentHitbox(Car *car);
	~carDentHitbox();

	//std::vector<sf::CircleShape*> getOneCollisionHitbox(const Car::hitboxPosition &pos);
	//Car::collisionSide *getLastCollisionSide();

	std::vector<std::pair<sf::CircleShape*, std::pair<sf::Vector2f, float*>>> getVector();

	void draw();

private:

	Car * car;

	std::vector<std::pair<sf::CircleShape*, std::pair<sf::Vector2f, float*>>> hitboxes;

	void setHitbox(const sf::Vector2f &range, const sf::Vector2f &moveOffset, const float &bufValue, const sf::Color &color = sf::Color::White);
	// <hitbox, index> , <moveOffset, cooldown>

	//void setHitbox(std::vector<sf::CircleShape*>&hitbox, const sf::Vector2f &range, const sf::Color &color = sf::Color::White);
};