#include "carCollisionWithCar.hpp"

#include "Collision.hpp"

#include <iostream>

Car::collisionSide carCollisionWithCar::checkCollisions(Car * car1, Car * car2, bool react)
{
	if (car1 == car2)
		return Car::collisionSide::None;

	if (car1->getGlobalBounds().intersects(car2->getGlobalBounds()))
	{
		auto &instance = Instance();
		instance.car1 = car1;
		instance.car2 = car2;
		instance.speed = static_cast<float>(std::max(car1->getSpeed(), car2->getSpeed()));

		float powerFirst = static_cast<float>(pow(car1->getSpeed(), 2.f) / car1->getWeight());
		float powerSecond = static_cast<float>(pow(car2->getSpeed(), 2.f) / car2->getWeight());

		if (powerSecond > powerFirst)
			std::swap(car1, car2);

		std::pair<Car::collisionSide, Car::collisionSide> carSidesOfCollision = instance.whereIsCollision();

		//std::cout << static_cast<int>(carSidesOfCollision.first) << ' ' << static_cast<int>(carSidesOfCollision.second) << std::endl;

		sf::Vector2f v(0,0);
		float angle = 0;

		if (react)
		{
			car1->getBoolIsCollision(carSidesOfCollision.first) = true;
			car2->getBoolIsCollision(carSidesOfCollision.second) = true;
			*car1->getLastCollisionSide() = carSidesOfCollision.first;
			*car2->getLastCollisionSide() = carSidesOfCollision.second;

			switch (carSidesOfCollision.first)
			{
			case Car::collisionSide::Front:
			case Car::collisionSide::Back:
			case Car::collisionSide::Left:
			case Car::collisionSide::Right:

				switch (carSidesOfCollision.second)
				{
				case Car::collisionSide::Front:
				case Car::collisionSide::Back:
				case Car::collisionSide::Left:
				case Car::collisionSide::Right:

					if (car1->getSpeed() >4)
					{
						v = instance.moveFromCar(car2, car1, std::make_pair(carSidesOfCollision.second, carSidesOfCollision.first));
						car2->setPowerOfCrashMove(v * static_cast<float>(car1->getSpeed()) / 5.f);
						
						if (v != sf::Vector2f(0, 0))
							car1->setSpeed(1.8f);
					}
					else
					{
						if (car1->getStateMoving() == 0) // front
							car1->setSpeed(0);
					}

					break;
				case Car::collisionSide::RightUp:
				case Car::collisionSide::LeftUp:
				case Car::collisionSide::LeftDown:
				case Car::collisionSide::RightDown:

					if (car1->getSpeed() > 1)
					{
						angle = instance.howManyRotate(car2, car1, std::make_pair(carSidesOfCollision.second, carSidesOfCollision.first));
						car2->setPowerOfCrashRotate(std::make_pair(0, angle* static_cast<float>(car1->getSpeed())));
						
						if (angle != 0)
						{
							if (car1->getSpeed() > 2.f)
								car1->setSpeed(static_cast<float>(car1->getSpeed()) / 1.2f);
							else
								car1->setSpeed(1.f);
						}
					}
					else
					{
						if (car1->getStateMoving() == 0) // front
							car1->setSpeed(0);
					}

					break;
				}

				break;
			case Car::collisionSide::RightUp:
			case Car::collisionSide::LeftUp:
			case Car::collisionSide::LeftDown:
			case Car::collisionSide::RightDown:

				switch (carSidesOfCollision.second)
				{
				case Car::collisionSide::Front:
				case Car::collisionSide::Right:
				case Car::collisionSide::Back:
				case Car::collisionSide::Left:

					if (car1->getSpeed() >2)
					{
						v = instance.moveFromCar(car2, car1, std::make_pair(carSidesOfCollision.second, carSidesOfCollision.first));
						car2->setPowerOfCrashMove(v * static_cast<float>(car1->getSpeed()) / 5.f);

						angle = instance.howManyRotate(car1, car2, std::make_pair(carSidesOfCollision.first, carSidesOfCollision.second));
						car1->setPowerOfCrashRotate(std::make_pair(0, angle));

						if (v != sf::Vector2f(0, 0))
							car1->setSpeed(1.8f);
					}
					else
					{
						if (car1->getStateMoving() == 0) // front
							car1->setSpeed(0);
					}

					break;
				case Car::collisionSide::RightUp:
				case Car::collisionSide::LeftUp:
				case Car::collisionSide::LeftDown:
				case Car::collisionSide::RightDown:

					if (car1->getSpeed() > 1)
					{
						angle = instance.howManyRotate(car2, car1, std::make_pair(carSidesOfCollision.second, carSidesOfCollision.first));
						float angle2 = instance.howManyRotate(car1, car2, std::make_pair(carSidesOfCollision.first, carSidesOfCollision.second));
						car1->setPowerOfCrashRotate(std::make_pair(0, angle2));
						car2->setPowerOfCrashRotate(std::make_pair(0, angle* 1.1f));

						if (angle != 0)
						{
							if (car1->getSpeed() > 2.f)
								car1->setSpeed(static_cast<float>(car1->getSpeed()) / 1.2f);
							else
								car1->setSpeed(1.f);
						}
					}
					else
					{
						if (car1->getStateMoving() == 0) // front
							car1->setSpeed(0);
					}
					break;
				}
				break;
			}
		}
		return carSidesOfCollision.first;
	}
	return Car::collisionSide::None;
}

std::pair<Car::collisionSide, Car::collisionSide> carCollisionWithCar::whereIsCollision()
{
	size_t orderCheckingHitbox[]{ 1, 7, 3, 5, 0, 4, 6, 2};
	for (auto i = 0;i < 8;++i)
		for (auto j = 0;j < 8;++j)
			if (checkCollisionBetweenTwoCars(std::make_pair(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(orderCheckingHitbox[i])), car2->getCollisionHitbox(static_cast<Car::hitboxPosition>(orderCheckingHitbox[j]))),
				std::make_pair(&car1->getBoolIsCollision(static_cast<Car::collisionSide>(orderCheckingHitbox[i])), &car2->getBoolIsCollision(static_cast<Car::collisionSide>(orderCheckingHitbox[j])))))

				return std::make_pair(static_cast<Car::collisionSide>(orderCheckingHitbox[i]), static_cast<Car::collisionSide>(orderCheckingHitbox[j]));

	return std::make_pair(Car::collisionSide::None, Car::collisionSide::None);
}

bool carCollisionWithCar::checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, const std::pair<bool*, bool*>&isCollision)
{
	for (const auto &i : hitbox.first)
		for (const auto &j : hitbox.second)
		{
			sf::Vector2f vector = Collision::getCenterOfHitbox(*j) - Collision::getCenterOfHitbox(*i);
			float length = sqrt(vector.x*vector.x + vector.y * vector.y);

			if (length < 4)
				return true;
		}

	*isCollision.first = false;
	*isCollision.second = false;
	return false;
}

float carCollisionWithCar::howManyRotate(Car *car1, Car *car2, const std::pair<Car::collisionSide, Car::collisionSide>&side)
{
	float rotate = 0.0f;
	const float singleRotateValue = 0.05f;

	while (checkCollisionBetweenTwoCars(std::make_pair(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)), car2->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.second))),
		std::make_pair(&car1->getBoolIsCollision(side.first), &car2->getBoolIsCollision(side.second))))
	{
		switch (side.first)
		{
		case Car::collisionSide::LeftUp:
		case Car::collisionSide::RightDown: // +

			rotate += singleRotateValue;
			Collision::rotateOneHitbox(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)), singleRotateValue);

			break;
		case Car::collisionSide::RightUp:
		case Car::collisionSide::LeftDown: // -

			rotate -= singleRotateValue;
			Collision::rotateOneHitbox(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)), -singleRotateValue);

			break;
		}
	}
	Collision::rotateOneHitbox(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)), -rotate);
	return rotate;
}

sf::Vector2f carCollisionWithCar::moveFromCar(Car *car1,Car *car2,const std::pair<Car::collisionSide,Car::collisionSide>&side)
{
	sf::Vector2f v(sf::Vector2f(0, 0));
	sf::Vector2f w;
	while (checkCollisionBetweenTwoCars(std::make_pair(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)),car2->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.second))),
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
		case Car::collisionSide::Front:
			w = car1->getMovementVector(car1->getSprite()->getRotation() + 180);
			break;
		case Car::collisionSide::Back:
			w = car1->getMovementVector();
			break;
		}
		v.x += w.x;
		v.y += w.y;

		Collision::moveOneHitbox(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)), w);
	}
	Collision::moveOneHitbox(car1->getCollisionHitbox(static_cast<Car::hitboxPosition>(side.first)), -v);
	return v;
}