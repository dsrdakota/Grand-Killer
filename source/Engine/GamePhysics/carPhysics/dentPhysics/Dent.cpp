#include "Dent.hpp"

#include <iostream>

void carDentPhysics::doDents(Car * car)
{
	//checkCollision(car);
}

void carDentPhysics::checkCollision(Car * car)
{
	auto allHitboxes = car->getAllHitboxes();

	auto allDentHitboxes = car->getDentHitbox();

	for (size_t i = 0;i < allHitboxes.size();++i)
		if (Map::isPointInCollisionArea(getCenterOfHitbox(*allHitboxes[i])))
			doDentInCar(car, allDentHitboxes[i], i);
}

void carDentPhysics::doDentInCar(Car * car,const std::pair<sf::CircleShape*, std::pair<sf::Vector2f, float*>>&dent, const size_t & index)
{
	if (*dent.second.second > 0)
	{
		auto carShape = car->getShape()->getShape();
		auto carShadow = car->getShadow()->getShape();

		float powerOfDent = car->getSpeed() / 40.f;

		if ((index >= 0 && index < 50) || // front
			index >= 485 && index < car->getAllHitboxes().size()) // back
			powerOfDent *= 2;


		carShape->setPoint(index,sf::Vector2f(carShape->getPoint(index).x + dent.second.first.x * powerOfDent,
			carShape->getPoint(index).y + dent.second.first.y * powerOfDent));

		carShadow->setPoint(index, sf::Vector2f(carShadow->getPoint(index).x + dent.second.first.x * powerOfDent,
			carShadow->getPoint(index).y + dent.second.first.y * powerOfDent));

		*dent.second.second -= powerOfDent ;
		
		auto allHitboxes = car->getAllHitboxes();
		allHitboxes[index]->setOrigin(carShape->getOrigin() - carShape->getPoint(index));
		allHitboxes[index]->setPosition(carShape->getPosition());
	}
}

sf::Vector2f carDentPhysics::getCenterOfHitbox(const sf::CircleShape & hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}
