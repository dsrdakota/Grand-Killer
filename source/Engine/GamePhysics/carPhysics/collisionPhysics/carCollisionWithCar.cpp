#include "carCollisionWithCar.hpp"

#include "Collision.hpp"

#include <iostream>

Car::collisionSide carCollisionWithCar::checkCollisions(Car * car1, Car * car2, bool react)
{
	if (car1 == car2)
		return Car::collisionSide::None;
	
	if (car1->getSprite()->getGlobalBounds().intersects(car2->getSprite()->getGlobalBounds()))
	{
		auto &instance = Instance();
		instance.car1 = car1;
		instance.car2 = car2;

		std::pair<Car::collisionSide, Car::collisionSide> carSidesOfCollision = instance.whereIsCollision();

		std::cout << static_cast<int>(carSidesOfCollision.first) << ' ' << static_cast<int>(carSidesOfCollision.second) << std::endl;

		sf::Vector2f v(0,0);
		float angle = 0;

		if (react)
		{
			switch (carSidesOfCollision.first)
			{
			case Car::collisionSide::Front:

				switch (carSidesOfCollision.second)
				{
				case Car::collisionSide::Front:
					break;
				case Car::collisionSide::Right:

					car1->getBoolIsCollision(Car::collisionSide::Front) = true;
					car2->getBoolIsCollision(Car::collisionSide::Right) = true;
					*car1->getLastCollisionSide() = Car::collisionSide::Front;

					if (car1->getSpeed() >2)
					{
						car1->setSpeed(2.1f);
						v = instance.moveFromCar(car2, car1, std::make_pair(Car::collisionSide::Right, Car::collisionSide::Front));

						car2->setPowerOfCrash(v * static_cast<float>(car1->getSpeed()) );
					}
					else
					{
						if(car1->getStateMoving() ==0) // front
							car1->setSpeed(0);
					}

					break;
				case Car::collisionSide::Back:
					break;
				case Car::collisionSide::Left:
					break;
				}

				break;

			case Car::collisionSide::None:
				*car1->getLastCollisionSide() = Car::collisionSide::None;
				*car2->getLastCollisionSide() = Car::collisionSide::None;
				break;
			}
		}
		return carSidesOfCollision.first;
	}

	return Car::collisionSide::None;
}

std::pair<Car::collisionSide, Car::collisionSide> carCollisionWithCar::whereIsCollision()
{
	size_t orderCheckingHitbox[]{ 0 ,4,1,7,3,5,6,2 };

	for (auto i = 0;i < 8;++i)
		for (auto j = 0;j < 8;++j)
			if (checkCollisionBetweenTwoCars(std::make_pair(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(orderCheckingHitbox[i])), car2->getCollisionHitbox(static_cast<Car::hitboxPosition>(orderCheckingHitbox[j]))),
				car1->getBoolIsCollision(static_cast<Car::collisionSide>(orderCheckingHitbox[i])), car2->getBoolIsCollision(static_cast<Car::collisionSide>(orderCheckingHitbox[j]))))
				return std::make_pair(static_cast<Car::collisionSide>(orderCheckingHitbox[i]), static_cast<Car::collisionSide>(orderCheckingHitbox[j]));

	return std::make_pair(Car::collisionSide::None, Car::collisionSide::None);
}

bool carCollisionWithCar::checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, bool &isCollision1, bool &isCollision2)
{
	for (const auto &i : hitbox.first)
		for (const auto &j : hitbox.second)
			if (i->getGlobalBounds().intersects(j->getGlobalBounds()))
				return true;

	isCollision1 = false;
	isCollision2 = false;
	return false;
}

void carCollisionWithCar::rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle)
{
	for (const auto &i : hitbox)
		i->rotate(angle);
}

void carCollisionWithCar::moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset)
{
	for (const auto &i : hitbox)
		i->move(offset);
}

float carCollisionWithCar::howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide & side)
{
	/*float rotate = 0.0f;
	const float singleRotateValue = 0.05f;

	while (checkCollisionWithOneHitbox(hitbox, car1->getBoolIsCollision(side)))
	{
		switch (side)
		{
		case Car::collisionSide::LeftUp:
		case Car::collisionSide::RightDown: // +

			rotate += singleRotateValue;
			rotateOneHitbox(hitbox, singleRotateValue);

			break;
		case Car::collisionSide::RightUp:
		case Car::collisionSide::LeftDown: // -

			rotate -= singleRotateValue;
			rotateOneHitbox(hitbox, -singleRotateValue);

			break;
		}
	}
	return rotate;*/
	return 0;
}

sf::Vector2f carCollisionWithCar::moveFromCar(Car *car1,Car *car2,const std::pair<Car::collisionSide,Car::collisionSide>&side)
{
	sf::Vector2f v(sf::Vector2f(0, 0));
	sf::Vector2f w;
	while (checkCollisionWithOneHitbox(std::make_pair(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)),car2->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.second))),
		std::make_pair(&car1->getBoolIsCollision(side.first),&car2->getBoolIsCollision(side.second))))
	{
		switch (side.first)
		{
		case Car::collisionSide::RightUp:
		case Car::collisionSide::RightDown:
		case Car::collisionSide::Right:
			w = car1->getMovementVector(std::fmod(car1->getSprite()->getRotation() - static_cast<float>(*car1->getOverSteerValue()) - 90, 360.f));
			break;
		case Car::collisionSide::LeftUp:
		case Car::collisionSide::LeftDown:
		case Car::collisionSide::Left:
			w = car1->getMovementVector(std::fmod(car1->getSprite()->getRotation() - static_cast<float>(*car1->getOverSteerValue()) + 90, 360.f));
			break;
		}
		v.x += w.x;
		v.y += w.y;

		moveOneHitbox(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)), sf::Vector2f(w));
	}
	return v/3.f;
}

bool carCollisionWithCar::checkCollisionWithOneHitbox(const std::pair<std::vector<sf::CircleShape*>,std::vector<sf::CircleShape*>>&hitbox, const std::pair<bool*,bool*>&isCollision)
{
	//for (const auto &i : hitbox)
		//if (Map::isPointInCollisionArea(getCenterOfHitbox(*i)))
			//return true;

	for (const auto &i : hitbox.first)
		for (const auto &j : hitbox.second)
			if (i->getGlobalBounds().intersects(j->getGlobalBounds()))
				return true;

	*isCollision.first = false;
	*isCollision.second = false;
	return false;
}

sf::Vector2f carCollisionWithCar::getCenterOfHitbox(const sf::CircleShape & hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}