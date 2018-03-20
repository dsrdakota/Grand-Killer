#include "carWithCar.hpp"

Hitbox::collisionSide carWithCar::checkCollisions(Car * car1, Car * car2, bool react)
{
	if (car1 == car2)
		return Hitbox::collisionSide::None;

	if (car1->getGlobalBounds().intersects(car2->getGlobalBounds()))
	{
		auto &instance = Instance();
		instance.car1 = car1;
		instance.car2 = car2;

		instance.powerFirst = static_cast<float>(*car1->getMovementClass()->getSpeed() * car1->getWeight());
		instance.powerSecond = static_cast<float>(*car2->getMovementClass()->getSpeed() * car2->getWeight());

		if (instance.powerSecond > instance.powerFirst)
			std::swap(car1, car2);

		std::pair<Hitbox::collisionSide, Hitbox::collisionSide> carSidesOfCollision = instance.whereIsCollision();

		sf::Vector2f v(0,0);
		float angle = 0;

		if (react)
		{
			switch (carSidesOfCollision.first)
			{
			case Hitbox::collisionSide::Front:

				car1->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Front) = true;
				*car1->getHitboxClass()->getLastCollisionSide() = Hitbox::collisionSide::Front;
				if (car1->getMovementClass()->getStateMoving() == 0) // front
				{

					switch (carSidesOfCollision.second)
					{
					case Hitbox::collisionSide::Front:
					case Hitbox::collisionSide::Back:
					case Hitbox::collisionSide::Left:
					case Hitbox::collisionSide::Right:

						car2->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.second) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Hitbox::collisionSide::RightUp:
					case Hitbox::collisionSide::RightDown:

						car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Hitbox::collisionSide::LeftUp:
					case Hitbox::collisionSide::LeftDown:

						car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
				}
				break;
			case Hitbox::collisionSide::Back:

				car1->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Back) = true;
				*car1->getHitboxClass()->getLastCollisionSide() = Hitbox::collisionSide::Back;
				if (car1->getMovementClass()->getStateMoving() == 1) // front
				{

					switch (carSidesOfCollision.second)
					{
					case Hitbox::collisionSide::Front:
					case Hitbox::collisionSide::Back:
					case Hitbox::collisionSide::Left:
					case Hitbox::collisionSide::Right:

						car2->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.second) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Hitbox::collisionSide::RightUp:
					case Hitbox::collisionSide::RightDown:

						car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					case Hitbox::collisionSide::LeftUp:
					case Hitbox::collisionSide::LeftDown:

						car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
						instance.collisionIs(car1, car2, carSidesOfCollision);

						break;

					}
				}

				break;
			case Hitbox::collisionSide::Left:
			case Hitbox::collisionSide::Right:

				car1->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.first) = true;
				switch (carSidesOfCollision.second)
				{
				case Hitbox::collisionSide::Front:
				case Hitbox::collisionSide::Back:
				case Hitbox::collisionSide::Left:
				case Hitbox::collisionSide::Right:

					car2->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.second) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::RightUp:
				case Hitbox::collisionSide::RightDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::LeftUp:
				case Hitbox::collisionSide::LeftDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				}

				break;
			case Hitbox::collisionSide::RightUp:

				car1->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;

				switch (carSidesOfCollision.second)
				{
				case Hitbox::collisionSide::Front:
				case Hitbox::collisionSide::Back:
				case Hitbox::collisionSide::Left:
				case Hitbox::collisionSide::Right:

					car2->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.second) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::RightUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::RightDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::LeftUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::LeftDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				}

				break;
			case Hitbox::collisionSide::RightDown:

				car1->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;

				switch (carSidesOfCollision.second)
				{
				case Hitbox::collisionSide::Front:
				case Hitbox::collisionSide::Back:
				case Hitbox::collisionSide::Left:
				case Hitbox::collisionSide::Right:

					car2->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.second) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::RightUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::RightDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::LeftUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::LeftDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				}

				break;
			case Hitbox::collisionSide::LeftUp:

				car1->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;

				switch (carSidesOfCollision.second)
				{
				case Hitbox::collisionSide::Front:
				case Hitbox::collisionSide::Back:
				case Hitbox::collisionSide::Left:
				case Hitbox::collisionSide::Right:

					car2->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.second) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::RightUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::RightDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::LeftUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::LeftDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				}

				break;
			case Hitbox::collisionSide::LeftDown:

				car1->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;

				switch (carSidesOfCollision.second)
				{
				case Hitbox::collisionSide::Front:
				case Hitbox::collisionSide::Back:
				case Hitbox::collisionSide::Left:
				case Hitbox::collisionSide::Right:

					car2->getHitboxClass()->getBoolIsCollision(carSidesOfCollision.second) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::RightUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::RightDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				case Hitbox::collisionSide::LeftUp:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					if (*car1->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
						instance.collisionIs(car1, car2, carSidesOfCollision);

					break;
				case Hitbox::collisionSide::LeftDown:

					car2->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
					instance.collisionIs(car1, car2, carSidesOfCollision);

					break;

				}

				break;

			case Hitbox::collisionSide::None:
				*car1->getHitboxClass()->getLastCollisionSide() = Hitbox::collisionSide::None;
				*car2->getHitboxClass()->getLastCollisionSide() = Hitbox::collisionSide::None;

				break;
			}
		}
		return carSidesOfCollision.first;
	}
	return Hitbox::collisionSide::None;
}

std::pair<Hitbox::collisionSide, Hitbox::collisionSide> carWithCar::whereIsCollision()
{
	size_t orderCheckingHitbox[]{ 1, 7, 3, 5, 0, 4, 6, 2};
	for (auto i = 0;i < 8;++i)
		for (auto j = 0;j < 8;++j)
			if (checkCollisionBetweenTwoCars(std::make_pair(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(orderCheckingHitbox[i])), car2->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(orderCheckingHitbox[j]))),
				std::make_pair(&car1->getHitboxClass()->getBoolIsCollision(static_cast<Hitbox::collisionSide>(orderCheckingHitbox[i])), &car2->getHitboxClass()->getBoolIsCollision(static_cast<Hitbox::collisionSide>(orderCheckingHitbox[j])))))

				return std::make_pair(static_cast<Hitbox::collisionSide>(orderCheckingHitbox[i]), static_cast<Hitbox::collisionSide>(orderCheckingHitbox[j]));

	return std::make_pair(Hitbox::collisionSide::None, Hitbox::collisionSide::None);
}

bool carWithCar::checkCollisionBetweenTwoCars(std::pair<const std::vector<sf::CircleShape*>, const std::vector<sf::CircleShape*>>hitbox, const std::pair<bool*, bool*>&isCollision)
{
	for (const auto &i : hitbox.first)
	{
		if (car2->getGlobalBounds().intersects(i->getGlobalBounds()))
		{
			for (const auto &j : hitbox.second)
			{
				sf::Vector2f vector = Hitbox::getCenterOfHitbox(*j) - Hitbox::getCenterOfHitbox(*i);
				float length = sqrt(vector.x*vector.x + vector.y * vector.y);

				if (length < 4)
					return true;
			}
		}
	}

	*isCollision.first = false;
	*isCollision.second = false;
	return false;
}

float carWithCar::howManyRotate(Car *car1, Car *car2, const std::pair<Hitbox::collisionSide, Hitbox::collisionSide>&side)
{
	float rotate = 0.0f;
	const float singleRotateValue = 0.05f;

	while (checkCollisionBetweenTwoCars(std::make_pair(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.first)), car2->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.second))),
		std::make_pair(&car1->getHitboxClass()->getBoolIsCollision(side.first), &car2->getHitboxClass()->getBoolIsCollision(side.second))))
	{
		switch (side.first)
		{
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::RightDown: // +

			rotate += singleRotateValue;
			Hitbox::rotateOneHitbox(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.first)), singleRotateValue);

			break;
		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::LeftDown: // -

			rotate -= singleRotateValue;
			Hitbox::rotateOneHitbox(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.first)), -singleRotateValue);

			break;
		}
	}
	Hitbox::rotateOneHitbox(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.first)), -rotate);
	return rotate;
}

sf::Vector2f carWithCar::moveFromCar(Car *car1,Car *car2,const std::pair<Hitbox::collisionSide, Hitbox::collisionSide>&side)
{
	sf::Vector2f v(sf::Vector2f(0, 0));
	sf::Vector2f w;
	while (checkCollisionBetweenTwoCars(std::make_pair(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.first)),car2->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.second))),
		std::make_pair(&car1->getHitboxClass()->getBoolIsCollision(side.first),&car2->getHitboxClass()->getBoolIsCollision(side.second))))
	{
		switch (side.first)
		{
		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::RightDown:
		case Hitbox::collisionSide::Right:
			w = car1->getMovementClass()->getMovementVector(std::fmod(car1->getSprite()->getRotation() - static_cast<float>(*car1->getToTurnClass()->getSlidePhycics()->getOverSteer()) - 90, 360.f));
			break;
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::LeftDown:
		case Hitbox::collisionSide::Left:
			w = car1->getMovementClass()->getMovementVector(std::fmod(car1->getSprite()->getRotation() - static_cast<float>(*car1->getToTurnClass()->getSlidePhycics()->getOverSteer()) + 90, 360.f));
			break;
		case Hitbox::collisionSide::Front:
			w = car1->getMovementClass()->getMovementVector(car1->getSprite()->getRotation() + 180);
			break;
		case Hitbox::collisionSide::Back:
			w = car1->getMovementClass()->getMovementVector();
			break;
		}
		v.x += w.x;
		v.y += w.y;

		Hitbox::moveOneHitbox(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.first)), w);
	}
	Hitbox::moveOneHitbox(car1->getHitboxClass()->getCollisionHitbox(static_cast<Hitbox::hitboxPosition>(side.first)), -v);

	float multiplier = fabs(static_cast<float>(*car2->getMovementClass()->getSpeed() - *car1->getMovementClass()->getSpeed())) * 5.f / (static_cast<float>(*car1->getMovementClass()->getMaxSpeed() + *car2->getMovementClass()->getMaxSpeed()) / 2.f) * static_cast<float>(car2->getWeight()) / static_cast<float>(car1->getWeight());

	switch (side.second)
	{
	case Hitbox::collisionSide::Front:
	case Hitbox::collisionSide::Back:
		multiplier *= 1.2f;
		break;
	}

	return v * multiplier;
}

void carWithCar::collisionIs(Car * car1, Car * car2, const std::pair<Hitbox::collisionSide, Hitbox::collisionSide>& side)
{
	auto &instance = Instance();

	float angle = 0, angle2 = 0;
	sf::Vector2f v = sf::Vector2f(0, 0);

	car1->getToTurnClass()->getSlidePhycics()->breakSlide();
	car2->getToTurnClass()->getSlidePhycics()->breakSlide();

	switch (side.first)
	{
	case Hitbox::collisionSide::Front:
	case Hitbox::collisionSide::Back:

		switch (side.second)
		{
		case Hitbox::collisionSide::Front:
		case Hitbox::collisionSide::Back:
		case Hitbox::collisionSide::Left:
		case Hitbox::collisionSide::Right:

			if (*car1->getMovementClass()->getSpeed() > 1)
			{
				v = instance.moveFromCar(car2, car1, std::make_pair(side.second, side.first));

				if (car2->getMovementClass()->isMoveAble())
					car2->move(v);

				car2->getMovementClass()->setPowerOfCrashMove(std::make_pair(v, fabs(powerFirst - powerSecond)));

				if (v != sf::Vector2f(0, 0) && car2->getMovementClass()->isMoveAble())
				{
					if (*car1->getMovementClass()->getSpeed() > 5.f)
						car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 5.f);
					else
						car1->getMovementClass()->setSpeed(0.8f);

					car2->getMovementClass()->setSpeed(0.f);
				}
			}

			break;

		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::LeftDown:
		case Hitbox::collisionSide::RightDown:

			angle = instance.howManyRotate(car2, car1, std::make_pair(side.second, side.first));
			car2->getMovementClass()->setPowerOfCrashRotate(std::make_pair(0.f, angle * static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.2f));

			if (angle != 0 && car2->getMovementClass()->isRotateAble())
			{
				if (*car1->getMovementClass()->getSpeed() > 1.f)
					car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.2f);
				else
					car1->getMovementClass()->setSpeed(0.f);

				car2->getMovementClass()->setSpeed(0.f);
			}

			break;
		}

		break;
	case Hitbox::collisionSide::Left:
	case Hitbox::collisionSide::Right:
	
		switch (side.second)
		{
		case Hitbox::collisionSide::Front:
		case Hitbox::collisionSide::Back:
		case Hitbox::collisionSide::Left:
		case Hitbox::collisionSide::Right:

			v = instance.moveFromCar(car2, car1, std::make_pair(side.second, side.first));

			if (car2->getMovementClass()->isMoveAble())
				car2->move(v);

			car2->getMovementClass()->setPowerOfCrashMove(std::make_pair(v, fabs(powerFirst - powerSecond)));

			if (v != sf::Vector2f(0, 0) && car2->getMovementClass()->isMoveAble())
				car2->getMovementClass()->setSpeed(0.f);

			car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.1f);

			break;

		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::LeftDown:
		case Hitbox::collisionSide::RightDown:

			angle = instance.howManyRotate(car2, car1, std::make_pair(side.second, side.first));
			car2->getMovementClass()->setPowerOfCrashRotate(std::make_pair(0.f, angle * static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.5f));

			if (angle != 0 && car2->getMovementClass()->isRotateAble())
				car2->getMovementClass()->setSpeed(0.f);

			car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.1f);

			break;
		}
		break;

	case Hitbox::collisionSide::RightUp:
	case Hitbox::collisionSide::LeftUp:

		switch (side.second)
		{
		case Hitbox::collisionSide::Front:
		case Hitbox::collisionSide::Right:
		case Hitbox::collisionSide::Back:
		case Hitbox::collisionSide::Left:
	
			if (car1->getMovementClass()->getStateMoving() == 0) // front
			{
				angle2 = instance.howManyRotate(car1, car2, std::make_pair(side.first, side.second));
				car1->rotate(angle2);
			}
			else if (car1->getMovementClass()->getStateMoving() == 1) // back
			{
				v = instance.moveFromCar(car1, car2, std::make_pair(side.first, side.second));
				car1->move(v);
			}

			v = instance.moveFromCar(car2, car1, std::make_pair(side.second, side.first));

			if (car2->getMovementClass()->isMoveAble())
				car2->move(v);

			car2->getMovementClass()->setPowerOfCrashMove(std::make_pair(v, fabs(powerFirst - powerSecond)));

			if(v != sf::Vector2f(0,0))
				car2->getMovementClass()->setSpeed(0.f);

			car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.1f);

			break;
		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::LeftDown:
		case Hitbox::collisionSide::RightDown:

			if (car1->getMovementClass()->getStateMoving() == 0) // front
			{
				angle2 = instance.howManyRotate(car1, car2, std::make_pair(side.first, side.second));
				car1->rotate(angle2);

			}
			else if (car1->getMovementClass()->getStateMoving() == 1) // back
			{
				v = instance.moveFromCar(car1, car2, std::make_pair(side.first, side.second));
				car1->move(v);
			}

			angle = instance.howManyRotate(car2, car1, std::make_pair(side.second, side.first));
			car2->getMovementClass()->setPowerOfCrashRotate(std::make_pair(0.f, angle * static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.2f));

			if (angle != 0)
				car2->getMovementClass()->setSpeed(0.f);

			car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.05f);

			break;
		}
		break;

	case Hitbox::collisionSide::LeftDown:
	case Hitbox::collisionSide::RightDown:

		switch (side.second)
		{
		case Hitbox::collisionSide::Front:
		case Hitbox::collisionSide::Right:
		case Hitbox::collisionSide::Back:
		case Hitbox::collisionSide::Left:

			if (car1->getMovementClass()->getStateMoving() == 1) // back
			{
				angle2 = instance.howManyRotate(car1, car2, std::make_pair(side.first, side.second));
				car1->rotate(angle2);

			}
			else if (car1->getMovementClass()->getStateMoving() == 0) // front
			{
				v = instance.moveFromCar(car1, car2, std::make_pair(side.first, side.second));
				car1->move(v);
			}

			v = instance.moveFromCar(car2, car1, std::make_pair(side.second, side.first));

			if(car2->getMovementClass()->isMoveAble())
				car2->move(v);

			car2->getMovementClass()->setPowerOfCrashMove(std::make_pair(v, fabs(powerFirst - powerSecond)));

			if (v != sf::Vector2f(0, 0))
				car2->getMovementClass()->setSpeed(0.f);

			car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.1f);

			break;
		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::LeftDown:
		case Hitbox::collisionSide::RightDown:

			if (car1->getMovementClass()->getStateMoving() == 1) // back
			{
				angle2 = instance.howManyRotate(car1, car2, std::make_pair(side.first, side.second));
				car1->rotate(angle2);

			}
			else if (car1->getMovementClass()->getStateMoving() == 0) // front
			{
				v = instance.moveFromCar(car1, car2, std::make_pair(side.first, side.second));
				car1->move(v);
			}

			angle = instance.howManyRotate(car2, car1, std::make_pair(side.second, side.first));
			car2->getMovementClass()->setPowerOfCrashRotate(std::make_pair(0.f, angle * static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.2f));

			if (angle != 0)
				car2->getMovementClass()->setSpeed(0.f);

			car1->getMovementClass()->setSpeed(static_cast<float>(*car1->getMovementClass()->getSpeed()) / 1.05f);

			break;
		}
		break;
	}
}