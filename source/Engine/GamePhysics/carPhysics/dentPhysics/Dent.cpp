#include "Dent.hpp"

#include <iostream>

void carDentPhysics::doDents(Car * car)
{
	int indexCollisionHitbox = checkCollision(car);

	if (indexCollisionHitbox != -1)
	{
		size_t begin = 0, end = 0;

		auto allDentHitboxes = car->getDentHitbox();

		const unsigned longDent = 10;

		begin = indexCollisionHitbox - longDent;

		if (indexCollisionHitbox + longDent > allDentHitboxes.size() - 1)
			end = indexCollisionHitbox + longDent - allDentHitboxes.size() - 1;
		else
			end = indexCollisionHitbox + longDent -1;

		float power = 1.1;

		if (end > allDentHitboxes.size()-1)
			for (size_t i = begin; i < allDentHitboxes.size();++i, i < (begin + allDentHitboxes.size() - 1) / 2 ? power += 0.2f : power -= 0.2f)
				doDentInCar(car, allDentHitboxes[i], power, i);
		else
			for (size_t i = begin; i < end;++i)
			{
				doDentInCar(car, allDentHitboxes[i], power, i);

				if (i < (begin+end) / 2)
					power += 0.2f;
				else
					power -= 0.2f;
			}
	
	}
}

size_t carDentPhysics::checkCollision(Car * car)
{
	auto allHitboxes = car->getAllHitboxes();

	for (size_t i = 0;i < allHitboxes.size();++i)
		if (Map::isPointInCollisionArea(getCenterOfHitbox(*allHitboxes[i])))
			return i;
	return -1;
}

void carDentPhysics::doDentInCar(Car * car,const std::pair<sf::CircleShape*, std::pair<sf::Vector2f, float*>>&dent, const float &power, const size_t & index)
{
	if (*dent.second.second > 0)
	{
		auto carShape = car->getShape()->getShape();
		auto carShadow = car->getShadow()->getShape();

		float powerOfDent = car->getSpeed() / 10.f * power;

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
