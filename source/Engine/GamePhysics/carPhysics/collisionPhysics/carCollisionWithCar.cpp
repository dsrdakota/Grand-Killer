#include "carCollisionWithCar.hpp"

#include <iostream>

void carCollisionWithCar::checkCollisions(Car * car1, Car * car2)
{
	if (car1->getSprite()->getGlobalBounds().intersects(car2->getSprite()->getGlobalBounds()))
	{
		std::cout << "Kolizja" << std::endl;
	}
}

sf::Vector2f carCollisionWithCar::getCenterOfHitbox(const sf::CircleShape & hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}
