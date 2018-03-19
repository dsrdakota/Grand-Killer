#include "carWithWall.hpp"

#include "../../Map/Map.hpp"

Hitbox::collisionSide carWithWall::checkCollisions(Car *car, bool react)
{
	auto &instance = Instance();
	instance.car = car;
	Hitbox::collisionSide collisionSide = instance.whereIsCollision();

	if (react)
	{
		switch (collisionSide)
		{
		case Hitbox::collisionSide::Front:

			if (instance.car->getMovementClass()->getStateMoving() == 0) // front
				instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Front), collisionSide);

			break;
		case Hitbox::collisionSide::Back:

			if (car->getMovementClass()->getStateMoving() == 1) // back
				instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Back), collisionSide);

			break;
		case Hitbox::collisionSide::Left:

			instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Left), collisionSide);

			break;
		case Hitbox::collisionSide::Right:

			instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Right), collisionSide);

			break;
		case Hitbox::collisionSide::RightUp:

			instance.car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;

			if (*car->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
				instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::upRight), collisionSide);

			break;
		case Hitbox::collisionSide::RightDown:

			instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::downRight), collisionSide);

			break;
		case Hitbox::collisionSide::LeftUp:

			instance.car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;

			if (*car->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
				instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::upLeft), collisionSide);

			break;
		case Hitbox::collisionSide::LeftDown:

			instance.collisionIs(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::downLeft), collisionSide);

			break;
		case Hitbox::collisionSide::None:
			*car->getHitboxClass()->getLastCollisionSide() = Hitbox::collisionSide::None;
			break;
		}
	}

	return collisionSide;
}

Hitbox::collisionSide carWithWall::whereIsCollision()
{
	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Front), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Front)))
		return Hitbox::collisionSide::Front;

	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Back), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Back)))
		return Hitbox::collisionSide::Back;

	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::upRight), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right)))
		return Hitbox::collisionSide::RightUp;

	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::upLeft), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left)))
		return Hitbox::collisionSide::LeftUp;

	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::downRight), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right)))
		return Hitbox::collisionSide::RightDown;

	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::downLeft), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left)))
		return Hitbox::collisionSide::LeftDown;

	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Left), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left)))
		return Hitbox::collisionSide::Left;

	if (checkCollisionWithOneHitbox(car->getHitboxClass()->getCollisionHitbox(Hitbox::hitboxPosition::Right), car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right)))
		return Hitbox::collisionSide::Right;

	return Hitbox::collisionSide::None;
}

bool carWithWall::checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>&hitbox, bool &isCollision)
{
	for (const auto &i : hitbox)
		if (Map::Instance().isPointInCollisionArea(Hitbox::getCenterOfHitbox(*i)))
			return true;

	isCollision = false;
	return false;
}

void carWithWall::collisionIs(const std::vector<sf::CircleShape*>&hitbox, const Hitbox::collisionSide &side)
{
	float angleRotate = 0;
	sf::Vector2f v = sf::Vector2f(0, 0);

	switch (side)
	{
	case Hitbox::collisionSide::Front:
	case Hitbox::collisionSide::Back:

		car->getHitboxClass()->getBoolIsCollision(side) = true;
		car->getMovementClass()->setSpeed(0);
		*car->getHitboxClass()->getLastCollisionSide() = side;

		break;
	case Hitbox::collisionSide::Left:
	case Hitbox::collisionSide::Right:

		car->getMovementClass()->setSpeed(static_cast<float>(*car->getMovementClass()->getSpeed() / 1.1f));
		v = moveFromWall(hitbox, side);
		Hitbox::moveOneHitbox(hitbox, -v);
		car->move(v);
		car->getHitboxClass()->getBoolIsCollision(side) = true;

		break;
	case Hitbox::collisionSide::LeftUp:
	case Hitbox::collisionSide::RightUp:

		if (*car->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Front)
		{
			car->getMovementClass()->setSpeed(static_cast<float>(*car->getMovementClass()->getSpeed() / 1.1f));

			if (car->getMovementClass()->getStateMoving() == 0) // front
			{
				car->getToTurnClass()->getSlidePhycics()->breakSlide();
				angleRotate = howManyRotate(hitbox, side);
				Hitbox::rotateOneHitbox(hitbox, angleRotate * -1.f);
				car->rotate(angleRotate);

			}
			else if (car->getMovementClass()->getStateMoving() == 1) // back
			{
				v = moveFromWall(hitbox, side);
				Hitbox::moveOneHitbox(hitbox, -v);
				car->move(v);
			}
		}

		break;
	case Hitbox::collisionSide::RightDown:
	case Hitbox::collisionSide::LeftDown:

		car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Left) = true;
		car->getHitboxClass()->getBoolIsCollision(Hitbox::collisionSide::Right) = true;

		if (*car->getHitboxClass()->getLastCollisionSide() != Hitbox::collisionSide::Back)
		{
			car->getMovementClass()->setSpeed(static_cast<float>(*car->getMovementClass()->getSpeed() / 1.1f));

			if (car->getMovementClass()->getStateMoving() == 1) // back
			{
				angleRotate = howManyRotate(hitbox, side);
				Hitbox::rotateOneHitbox(hitbox, angleRotate * -1.f);
				car->rotate(angleRotate);

			}
			else if (car->getMovementClass()->getStateMoving() == 0) // front
			{
				car->getToTurnClass()->getSlidePhycics()->breakSlide();
				v = moveFromWall(hitbox, side);
				Hitbox::moveOneHitbox(hitbox, -v);
				car->move(v);
			}
		}
		break;
	}
}

float carWithWall::howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Hitbox::collisionSide & side)
{
	float rotate = 0.0f;
	const float singleRotateValue = 0.05f;

	while (checkCollisionWithOneHitbox(hitbox, car->getHitboxClass()->getBoolIsCollision(side)))
	{
		switch (side)
		{
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::RightDown: // +

			rotate += singleRotateValue;
			Hitbox::rotateOneHitbox(hitbox, singleRotateValue);

			break;
		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::LeftDown: // -

			rotate -= singleRotateValue;
			Hitbox::rotateOneHitbox(hitbox, -singleRotateValue);

			break;
		}
	}
	return rotate;
}

sf::Vector2f carWithWall::moveFromWall(const std::vector<sf::CircleShape*> &hitbox, const Hitbox::collisionSide &side)
{
	sf::Vector2f v(sf::Vector2f(0, 0));
	sf::Vector2f w;
	while (checkCollisionWithOneHitbox(hitbox, car->getHitboxClass()->getBoolIsCollision(side)))
	{
		switch (side)
		{
		case Hitbox::collisionSide::RightUp:
		case Hitbox::collisionSide::RightDown:
		case Hitbox::collisionSide::Right:
			w = car->getMovementClass()->getMovementVector(std::fmod(car->getSprite()->getRotation() - static_cast<float>(*car->getToTurnClass()->getSlidePhycics()->getOverSteer()) - 90, 360.f));
			break;
		case Hitbox::collisionSide::LeftUp:
		case Hitbox::collisionSide::LeftDown:
		case Hitbox::collisionSide::Left:
			w = car->getMovementClass()->getMovementVector(std::fmod(car->getSprite()->getRotation() - static_cast<float>(*car->getToTurnClass()->getSlidePhycics()->getOverSteer()) + 90, 360.f));
			break;
		}
		v.x += w.x;
		v.y += w.y;

		Hitbox::moveOneHitbox(hitbox, sf::Vector2f(w));
	}
	return v;
}