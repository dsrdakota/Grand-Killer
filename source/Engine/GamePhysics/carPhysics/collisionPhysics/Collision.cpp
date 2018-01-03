#include "Collision.hpp"

#include "../../../../Manager/renderSprites.hpp"
#include "../../Map/Map.hpp"

Collision::Collision(Car * car)
{
	this->car = car;

	auto allHitboxes = car->getAllHitboxes();

	collisionArea = Map::Instance().getCollisionHitbox();

	lastCollisionSide = Car::collisionSide::None;

	setHitbox(upHitboxes, sf::Vector2f(10, 40), sf::Color(75, 0, 130));
	setHitbox(upRightHitboxes, sf::Vector2f(60, 100), sf::Color::Green);
	setHitbox(rightHitboxes, sf::Vector2f(101, 171), sf::Color::Blue);
	setHitbox(downRightHitboxes, sf::Vector2f(171, 240), sf::Color::Red);
	setHitbox(downHitboxes, sf::Vector2f(258, 300), sf::Color::Yellow);
	setHitbox(downLeftHitboxes, sf::Vector2f(315, 387), sf::Color::Magenta);
	setHitbox(leftHitboxes, sf::Vector2f(387, 457), sf::Color(83, 47, 40));
	setHitbox(upLeftHitboxes, sf::Vector2f(457, 497), sf::Color(255, 165, 0));
}

Collision::~Collision()
{
	
}

void Collision::checkCollisions()
{
	Car::collisionSide collisionSide = whereIsCollision();
	switch (collisionSide)
	{
	case Car::collisionSide::Front:

		if (car->getStateMoving() == 0) // front
			collisionIs(upHitboxes, collisionSide);

		break;
	case Car::collisionSide::Back:

		if (car->getStateMoving() == 1) // back
			collisionIs(downHitboxes, collisionSide);

		break;
	case Car::collisionSide::Left:

		collisionIs(leftHitboxes, collisionSide);

		break;
	case Car::collisionSide::Right:

		collisionIs(rightHitboxes, collisionSide);

		break;
	case Car::collisionSide::RightUp:

		car->getBoolIsCollision(Car::collisionSide::Right) = true;

		if (lastCollisionSide != Car::collisionSide::Front)
			collisionIs(upRightHitboxes, collisionSide);

		break;
	case Car::collisionSide::RightDown:

		collisionIs(downRightHitboxes, collisionSide);

		break;
	case Car::collisionSide::LeftUp:

		car->getBoolIsCollision(Car::collisionSide::Left) = true;

		if (lastCollisionSide != Car::collisionSide::Front)
			collisionIs(upLeftHitboxes, collisionSide);

		break;
	case Car::collisionSide::LeftDown:

		collisionIs(downLeftHitboxes, collisionSide);

			break;
	case Car::collisionSide::None:
		lastCollisionSide = Car::collisionSide::None;
		break;
	}
}

void Collision::setHitbox(std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & range, const sf::Color & color)
{
	auto allHitboxes = car->getAllHitboxes();

	for (size_t i = static_cast<size_t>(range.x);i <= static_cast<size_t>(range.y);i++)
	{
		hitbox.push_back(allHitboxes[i]);
		hitbox[hitbox.size() - 1]->setFillColor(color);
	}
}

Car::collisionSide Collision::whereIsCollision()
{
	if (checkCollisionWithOneHitbox(upHitboxes, car->getBoolIsCollision(Car::collisionSide::Front)))
		return Car::collisionSide::Front;

	if (checkCollisionWithOneHitbox(downHitboxes, car->getBoolIsCollision(Car::collisionSide::Back)))
		return Car::collisionSide::Back;

	if (checkCollisionWithOneHitbox(upRightHitboxes,car->getBoolIsCollision(Car::collisionSide::Right)))
		return Car::collisionSide::RightUp;

	if (checkCollisionWithOneHitbox(upLeftHitboxes, car->getBoolIsCollision(Car::collisionSide::Left)))
		return Car::collisionSide::LeftUp;

	if (checkCollisionWithOneHitbox(downRightHitboxes, car->getBoolIsCollision(Car::collisionSide::Right)))
		return Car::collisionSide::RightDown;

	if (checkCollisionWithOneHitbox(downLeftHitboxes, car->getBoolIsCollision(Car::collisionSide::Left)))
		return Car::collisionSide::LeftDown;

	if (checkCollisionWithOneHitbox(leftHitboxes, car->getBoolIsCollision(Car::collisionSide::Left)))
		return Car::collisionSide::Left;

	if (checkCollisionWithOneHitbox(rightHitboxes, car->getBoolIsCollision(Car::collisionSide::Right)))
		return Car::collisionSide::Right;

	return Car::collisionSide::None;
}

bool Collision::checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>&hitbox, bool &isCollision)
{
	for (const auto &i : hitbox)
		if (collisionArea->getPixel(static_cast<unsigned int>(i->getGlobalBounds().left + i->getGlobalBounds().width / 2),
			static_cast<unsigned int>(i->getGlobalBounds().top + i->getGlobalBounds().height / 2)) == sf::Color(255, 0, 0))
			return true;

	isCollision = false;
	return false;
}

void Collision::collisionIs(const std::vector<sf::CircleShape*>& hitbox, const Car::collisionSide & side)
{
	float angleRotate = 0;
	sf::Vector2f v = sf::Vector2f(0, 0);
	switch (side)
	{
	case Car::collisionSide::Front:
	case Car::collisionSide::Back:

		car->getBoolIsCollision(side) = true;
		car->setSpeed(0);
		lastCollisionSide = side;

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

		if (lastCollisionSide != Car::collisionSide::Back)
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

void Collision::rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle)
{
	for (const auto &i : hitbox)
		i->rotate(angle);
}

void Collision::moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset)
{
	for (const auto &i : hitbox)
		i->move(offset);
}

float Collision::howManyRotate(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide & side)
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

sf::Vector2f Collision::moveFromWall(const std::vector<sf::CircleShape*> &hitbox, const Car::collisionSide &side)
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