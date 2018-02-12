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

		sf::Vector2f v(0,0);
		float angle = 0;

		if (react)
		{
			switch (carSidesOfCollision.first)
			{
			case Car::collisionSide::Front:

				car1->getBoolIsCollision(Car::collisionSide::Front) = true;
				*car1->getLastCollisionSide() = Car::collisionSide::Front;
				if (car1->getStateMoving() == 0) // front
				{

					switch (carSidesOfCollision.second)
					{
					case Car::collisionSide::Front:
					case Car::collisionSide::Back:
					case Car::collisionSide::Left:
					case Car::collisionSide::Right:

							car2->getBoolIsCollision(carSidesOfCollision.second) = true;
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::RightUp:
					case Car::collisionSide::RightDown:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::LeftUp:
					case Car::collisionSide::LeftDown:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
				}
				break;
			case Car::collisionSide::Back:

				car1->getBoolIsCollision(Car::collisionSide::Back) = true;
				*car1->getLastCollisionSide() = Car::collisionSide::Back;
				if (car1->getStateMoving() == 1) // front
				{

					switch (carSidesOfCollision.second)
					{
					case Car::collisionSide::Front:
					case Car::collisionSide::Back:
					case Car::collisionSide::Left:
					case Car::collisionSide::Right:

						car2->getBoolIsCollision(carSidesOfCollision.second) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::RightUp:
					case Car::collisionSide::RightDown:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::LeftUp:
					case Car::collisionSide::LeftDown:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
				}

				break;
			case Car::collisionSide::Left:
			case Car::collisionSide::Right:

				car1->getBoolIsCollision(carSidesOfCollision.first) = true;
				switch (carSidesOfCollision.second)
				{
				case Car::collisionSide::Front:
				case Car::collisionSide::Back:
				case Car::collisionSide::Left:
				case Car::collisionSide::Right:

					car2->getBoolIsCollision(carSidesOfCollision.second) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Car::collisionSide::RightUp:
				case Car::collisionSide::RightDown:

					car2->getBoolIsCollision(Car::collisionSide::Right) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Car::collisionSide::LeftUp:
				case Car::collisionSide::LeftDown:

					car2->getBoolIsCollision(Car::collisionSide::Left) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				}

				break;
			case Car::collisionSide::RightUp:

				car1->getBoolIsCollision(Car::collisionSide::Right) = true;
				if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
				{

					switch (carSidesOfCollision.second)
					{
					case Car::collisionSide::Front:
					case Car::collisionSide::Back:
					case Car::collisionSide::Left:
					case Car::collisionSide::Right:

						car2->getBoolIsCollision(carSidesOfCollision.second) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::RightUp:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::RightDown:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::LeftUp:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::LeftDown:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
				}

				break;
			case Car::collisionSide::RightDown:

				car1->getBoolIsCollision(Car::collisionSide::Right) = true;
				if (*car1->getLastCollisionSide() != Car::collisionSide::Back)
				{

					switch (carSidesOfCollision.second)
					{
					case Car::collisionSide::Front:
					case Car::collisionSide::Back:
					case Car::collisionSide::Left:
					case Car::collisionSide::Right:

						car2->getBoolIsCollision(carSidesOfCollision.second) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::RightUp:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::RightDown:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::LeftUp:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::LeftDown:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
				}

				break;
			case Car::collisionSide::LeftUp:

				car1->getBoolIsCollision(Car::collisionSide::Left) = true;
				if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
				{

					switch (carSidesOfCollision.second)
					{
					case Car::collisionSide::Front:
					case Car::collisionSide::Back:
					case Car::collisionSide::Left:
					case Car::collisionSide::Right:

						car2->getBoolIsCollision(carSidesOfCollision.second) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::RightUp:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::RightDown:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::LeftUp:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::LeftDown:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
				}

				break;
			case Car::collisionSide::LeftDown:

				car1->getBoolIsCollision(Car::collisionSide::Left) = true;
				if (*car1->getLastCollisionSide() != Car::collisionSide::Back)
				{

					switch (carSidesOfCollision.second)
					{
					case Car::collisionSide::Front:
					case Car::collisionSide::Back:
					case Car::collisionSide::Left:
					case Car::collisionSide::Right:

						car2->getBoolIsCollision(carSidesOfCollision.second) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::RightUp:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::RightDown:

						car2->getBoolIsCollision(Car::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Car::collisionSide::LeftUp:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						if (*car1->getLastCollisionSide() != Car::collisionSide::Front)
							instance.collisionIs(car1, car2, carSidesOfCollision);

						break;
					case Car::collisionSide::LeftDown:

						car2->getBoolIsCollision(Car::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
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

	float multiplier = fabs(static_cast<float>(car2->getSpeed() - car1->getSpeed())) * 5.f / (static_cast<float>(car1->getMaxSpeed() + car2->getMaxSpeed()) / 2.f) * static_cast<float>(car2->getWeight()) / static_cast<float>(car1->getWeight());

	multiplier = fmod(multiplier, 2.5f);

	return v * multiplier;
}

void carCollisionWithCar::collisionIs(Car * car1, Car * car2, const std::pair<Car::collisionSide, Car::collisionSide>& side)
{
	auto &instance = Instance();

	float angle = 0, angle2 = 0;
	sf::Vector2f v = sf::Vector2f(0, 0);

	switch (side.first)
	{
	case Car::collisionSide::Front:
	case Car::collisionSide::Back:
	case Car::collisionSide::Left:
	case Car::collisionSide::Right:

		switch (side.second)
		{
		case Car::collisionSide::Front:
		case Car::collisionSide::Back:
		case Car::collisionSide::Left:
		case Car::collisionSide::Right:

			if (car1->getSpeed() > 2)
			{
				v = instance.moveFromCar(car2, car1, std::make_pair(side.second, side.first));
				car2->setPowerOfCrashMove(v);

				if (v != sf::Vector2f(0, 0))
				{
					if (car1->getSpeed() > 3.f)
						car1->setSpeed(static_cast<float>(car1->getSpeed()) / 1.2f);
					else
						car1->setSpeed(1.8f);
				}
			}
			else
				car1->setSpeed(0);

			break;
		case Car::collisionSide::RightUp:
		case Car::collisionSide::LeftUp:
		case Car::collisionSide::LeftDown:
		case Car::collisionSide::RightDown:

			if (car1->getSpeed() > 1)
			{
				angle = instance.howManyRotate(car2, car1, std::make_pair(side.second, side.first));
				car2->setPowerOfCrashRotate(std::make_pair(0.f, angle * static_cast<float>(car1->getSpeed()) / 2.f));

				if (angle != 0)
				{
					if (car1->getSpeed() > 2.f)
						car1->setSpeed(static_cast<float>(car1->getSpeed()) / 1.2f);
					else
						car1->setSpeed(1.f);
				}
			}
			else
				car1->setSpeed(0);

			break;
		}

		break;
	case Car::collisionSide::RightUp:
	case Car::collisionSide::LeftUp:
	case Car::collisionSide::LeftDown:
	case Car::collisionSide::RightDown:

		switch (side.second)
		{
		case Car::collisionSide::Front:
		case Car::collisionSide::Right:
		case Car::collisionSide::Back:
		case Car::collisionSide::Left:

			v = instance.moveFromCar(car2, car1, std::make_pair(side.second, side.first));
			car2->setPowerOfCrashMove(v);

			angle = instance.howManyRotate(car1, car2, std::make_pair(side.first, side.second));
			car1->setPowerOfCrashRotate(std::make_pair(0.f, angle));

			car1->setSpeed(static_cast<float>(car1->getSpeed()) / 1.1f);

			break;
		case Car::collisionSide::RightUp:
		case Car::collisionSide::LeftUp:
		case Car::collisionSide::LeftDown:
		case Car::collisionSide::RightDown:

			angle = instance.howManyRotate(car2, car1, std::make_pair(side.second, side.first));
			angle2 = instance.howManyRotate(car1, car2, std::make_pair(side.first, side.second));
			car1->setPowerOfCrashRotate(std::make_pair(0.f, angle2));
			car2->setPowerOfCrashRotate(std::make_pair(0.f, angle * static_cast<float>(car1->getSpeed()) / 2.f));

			car1->setSpeed(static_cast<float>(car1->getSpeed() / 1.1f));

			break;
		}
		break;
	}
}