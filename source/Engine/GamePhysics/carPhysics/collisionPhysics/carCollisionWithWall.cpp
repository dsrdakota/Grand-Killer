#include "carCollisionWithWall.hpp"

#include "carCollisionHitbox.hpp"
#include "Collision.hpp"
#include "../../../../Manager/renderSprites.hpp"
#include "../../Map/Map.hpp"

carCollisionWithWall::carCollisionWithWall()
{
	
}

carCollisionWithWall::~carCollisionWithWall()
{
	
}

void carCollisionWithWall::checkCollisions(Car *car)
{
	auto &instance = Instance();
	instance.car = car;
	Car::collisionSide collisionSide = instance.whereIsCollision();
	switch (collisionSide)
	{
	case Car::collisionSide::Front:

		if (instance.car->getStateMoving() == 0) // front
			instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::Front), collisionSide);

		break;
	case Car::collisionSide::Back:

		if (instance.car->getStateMoving() == 1) // back
			instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::Back), collisionSide);

		break;
	case Car::collisionSide::Left:

		instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::Left), collisionSide);

		break;
	case Car::collisionSide::Right:

		instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::Right), collisionSide);

		break;
	case Car::collisionSide::RightUp:

		instance.car->getBoolIsCollision(Car::collisionSide::Right) = true;

		if (*car->getLastCollisionSide() != Car::collisionSide::Front)
			instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::upRight), collisionSide);

		break;
	case Car::collisionSide::RightDown:

		instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::downRight), collisionSide);

		break;
	case Car::collisionSide::LeftUp:

		instance.car->getBoolIsCollision(Car::collisionSide::Left) = true;

		if (*car->getLastCollisionSide() != Car::collisionSide::Front)
			instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::upLeft), collisionSide);

		break;
	case Car::collisionSide::LeftDown:

		instance.collisionIs(car->getCollisionHitbox(Car::hitboxPosition::downLeft), collisionSide);

			break;
	case Car::collisionSide::None:
		*car->getLastCollisionSide() = Car::collisionSide::None;
		break;
	}
}

Car::collisionSide carCollisionWithWall::whereIsCollision()
{
	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::Front), car->getBoolIsCollision(Car::collisionSide::Front)))
		return Car::collisionSide::Front;

	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::Back), car->getBoolIsCollision(Car::collisionSide::Back)))
		return Car::collisionSide::Back;

	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::upRight),car->getBoolIsCollision(Car::collisionSide::Right)))
		return Car::collisionSide::RightUp;

	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::upLeft), car->getBoolIsCollision(Car::collisionSide::Left)))
		return Car::collisionSide::LeftUp;

	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::downRight), car->getBoolIsCollision(Car::collisionSide::Right)))
		return Car::collisionSide::RightDown;

	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::downLeft), car->getBoolIsCollision(Car::collisionSide::Left)))
		return Car::collisionSide::LeftDown;

	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::Left), car->getBoolIsCollision(Car::collisionSide::Left)))
		return Car::collisionSide::Left;

	if (checkCollisionWithOneHitbox(car->getCollisionHitbox(Car::hitboxPosition::Right), car->getBoolIsCollision(Car::collisionSide::Right)))
		return Car::collisionSide::Right;

	return Car::collisionSide::None;
}

bool carCollisionWithWall::checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>&hitbox, bool &isCollision)
{
	auto collisionArea = Map::Instance().getCollisionHitbox();
	for (const auto &i : hitbox)
		if (collisionArea->getPixel(i->getGlobalBounds().left + i->getGlobalBounds().width /2,
			i->getGlobalBounds().top + i->getGlobalBounds().height/2) == sf::Color(255,0,0))
			return true;

	isCollision = false;
	return false;
}

void carCollisionWithWall::collisionIs(const std::vector<sf::CircleShape*>&hitbox, const Car::collisionSide &side)
{
	float angleRotate = 0;
	sf::Vector2f v = sf::Vector2f(0, 0);
	switch (side)
	{
	case Car::collisionSide::Front:
	case Car::collisionSide::Back:

		car->getBoolIsCollision(side) = true;
		car->setSpeed(0);
		*car->getLastCollisionSide() = side;

		break;
	case Car::collisionSide::Left:
	case Car::collisionSide::Right:

		car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));
		v = moveFromWall(hitbox, side);
		moveOneHitbox(hitbox, -v);
		car->move(v);
		car->getBoolIsCollision(side) = true;

		break;
	case Car::collisionSide::LeftUp:
	case Car::collisionSide::RightUp:

		car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));
		car->breakSlide();
		angleRotate = howManyRotate(hitbox, side);
		rotateOneHitbox(hitbox, angleRotate * -1.f);
		car->rotate(angleRotate);

		break;
	case Car::collisionSide::RightDown:
	case Car::collisionSide::LeftDown:

		car->getBoolIsCollision(Car::collisionSide::Left) = true;
		car->getBoolIsCollision(Car::collisionSide::Right) = true;

		if (*car->getLastCollisionSide() != Car::collisionSide::Back)
		{
			if (car->getStateMoving() == 1) // back
			{
				car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));
				angleRotate = howManyRotate(hitbox, side);
				rotateOneHitbox(hitbox, angleRotate * -1.f);
				car->rotate(angleRotate);

			}
			else if (car->getStateMoving() == 0) // front
			{
				car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));
				car->breakSlide();
				v = moveFromWall(hitbox, side);
				moveOneHitbox(hitbox, -v);
				car->move(v);
			}
		}
		break;
	}
}

void carCollisionWithWall::rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle)
{
	for (const auto &i : hitbox)
		i->rotate(angle);
}

void carCollisionWithWall::moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset)
{
	for (const auto &i : hitbox)
		i->move(offset);
}

float carCollisionWithWall::howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide & side)
{
	float rotate = 0.0f;
	const float singleRotateValue = 0.05f;

	while (checkCollisionWithOneHitbox(hitbox, car->getBoolIsCollision(side)))
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
	return rotate;
}

sf::Vector2f carCollisionWithWall::moveFromWall(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide &side)
{
	sf::Vector2f v(sf::Vector2f(0,0));
	sf::Vector2f w;
	while (checkCollisionWithOneHitbox(hitbox,car->getBoolIsCollision(side)))
	{
		switch (side)
		{
		case Car::collisionSide::RightDown:
		case Car::collisionSide::Right:
			w = car->getMovementVector(std::fmod(car->getShape()->getShape()->getRotation() - static_cast<float>(*car->getOverSteerValue()) - 90, 360.f));
			break;
		case Car::collisionSide::LeftDown:
		case Car::collisionSide::Left:
			w = car->getMovementVector(std::fmod(car->getShape()->getShape()->getRotation() - static_cast<float>(*car->getOverSteerValue()) + 90, 360.f));
			break;
		}
		v.x += w.x;
		v.y += w.y;
		
		moveOneHitbox(hitbox, sf::Vector2f(w));
	}
	return v;
}

sf::Vector2f carCollisionWithWall::getCenterOfHitbox(const sf::CircleShape & hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}
