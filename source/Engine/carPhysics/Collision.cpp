#include "Collision.hpp"

#include "../../Manager/renderSprites.hpp"
#include <cmath>
#include <iostream>

Collision::Collision(Car * car)
{
	this->car = car;

	auto allHitboxes = car->getAllHitboxes();

	collisionArea = Map::Instance().getCollisionHitbox();

	lastCollisionSide = Car::collisionSide::None;

	setHitbox(upRightHitboxes, sf::Vector2f(34, 80), sf::Color::Green);
	setHitbox(rightHitboxes, sf::Vector2f(81, 206), sf::Color::Blue);
	setHitbox(downRightHitboxes, sf::Vector2f(207, 227), sf::Color::Red);
	setHitbox(downHitboxes, sf::Vector2f(275, 285), sf::Color::Yellow);
	setHitbox(downLeftHitboxes, sf::Vector2f(322, 342), sf::Color::Magenta);
	setHitbox(leftHitboxes, sf::Vector2f(343, 467), sf::Color(83, 47, 40));
	setHitbox(upLeftHitboxes, sf::Vector2f(468, 514), sf::Color(255, 165, 0));

	setHitbox(upHitboxes, sf::Vector2f(534,540), sf::Color(75, 0, 130));
	setHitbox(upHitboxes, sf::Vector2f(0, 6), sf::Color(75, 0, 130));
}

Collision::~Collision()
{
}

void Collision::checkCollisions()
{
	Car::collisionSide collisionSide = whereIsCollision();
	float angleRotate = 0;
	sf::Vector2f v = sf::Vector2f(0,0);
	switch (collisionSide)
	{
	case Car::collisionSide::Front:

		if (car->getStateMoving() == 0) // front
		{	
			car->getBoolIsCollision(collisionSide) = true;

			car->setSpeed(0);

			lastCollisionSide = Car::collisionSide::Front;
		}

		break;
	case Car::collisionSide::Back:

		if (car->getStateMoving() == 1) // back
		{
			car->getBoolIsCollision(collisionSide) = true;

			car->setSpeed(0);

			lastCollisionSide = Car::collisionSide::Back;
		}

		break;
	case Car::collisionSide::Left:

		car->setSpeed(static_cast<float>(car->getSpeed() / 1.1f));
		v = moveFromWall(leftHitboxes, Car::collisionSide::Left);
		moveOneHitbox(leftHitboxes, -v);
		car->move(v);
		car->getBoolIsCollision(collisionSide) = true;

		break;
	case Car::collisionSide::Right:

		car->setSpeed(static_cast<float>(car->getSpeed() / 1.1f));
		v = moveFromWall(rightHitboxes, Car::collisionSide::Right);
		moveOneHitbox(rightHitboxes, -v);
		car->move(v);
		car->getBoolIsCollision(collisionSide) = true;

		break;
	case Car::collisionSide::RightUp:

		car->getBoolIsCollision(Car::collisionSide::Right) = true;

		if (lastCollisionSide != Car::collisionSide::Front)
		{
			car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));

			angleRotate = howManyRotate(upRightHitboxes, Car::collisionSide::RightUp);

			rotateOneHitbox(upRightHitboxes, angleRotate * -1.f);

			car->rotate(angleRotate);
		}

		break;
	case Car::collisionSide::RightDown:

		car->getBoolIsCollision(Car::collisionSide::Left) = true;
		car->getBoolIsCollision(Car::collisionSide::Right) = true;

		if (lastCollisionSide != Car::collisionSide::Back)
		{
			car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));
			
			if (car->getStateMoving() == 1) // back
			{
				angleRotate = howManyRotate(downRightHitboxes, Car::collisionSide::RightDown);
				rotateOneHitbox(downRightHitboxes, angleRotate * -1.f);
				car->rotate(angleRotate);
			}
			else if (car->getStateMoving() == 0) // front
			{
				v = moveFromWall(downRightHitboxes, Car::collisionSide::RightDown);
				moveOneHitbox(downRightHitboxes, -v);
				car->move(v);
			}
		}

		break;
	case Car::collisionSide::LeftUp:

		car->getBoolIsCollision(Car::collisionSide::Left) = true;

		if (lastCollisionSide != Car::collisionSide::Front)
		{
			car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));

			angleRotate = howManyRotate(upLeftHitboxes, Car::collisionSide::LeftUp);

			rotateOneHitbox(upLeftHitboxes, angleRotate * -1.f);

			car->rotate(angleRotate);
		}

		break;
	case Car::collisionSide::LeftDown:

		car->getBoolIsCollision(Car::collisionSide::Left) = true;
		car->getBoolIsCollision(Car::collisionSide::Right) = true;

		if (lastCollisionSide != Car::collisionSide::Back)
		{
			car->setSpeed(static_cast<float>(car->getSpeed() / 1.085f));
			if (car->getStateMoving() == 1) // back
			{
				angleRotate = howManyRotate(downLeftHitboxes, Car::collisionSide::LeftDown);
				rotateOneHitbox(downLeftHitboxes, angleRotate * -1.f);
				car->rotate(angleRotate);
			}
			else if (car->getStateMoving() == 0) // front
			{
				v = moveFromWall(downLeftHitboxes, Car::collisionSide::LeftDown);
				moveOneHitbox(downLeftHitboxes, -v);
				car->move(v);
			}
		}

			break;
	case Car::collisionSide::None:
		lastCollisionSide = Car::collisionSide::None;
		break;
	}
}

void Collision::draw()
{
	/*for (const auto &i : upRightHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : rightHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : downRightHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : downHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : downLeftHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : leftHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : upLeftHitboxes)
		renderSprites::Instance().addToRender(i);

	for (const auto &i : upHitboxes)
		renderSprites::Instance().addToRender(i);*/
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
	if (checkCollisionWithOneHitbox(upHitboxes))
		return Car::collisionSide::Front;

	car->getBoolIsCollision(Car::collisionSide::Front) = false;

	if (checkCollisionWithOneHitbox(downHitboxes))
		return Car::collisionSide::Back;

	car->getBoolIsCollision(Car::collisionSide::Back) = false;


	if (checkCollisionWithOneHitbox(leftHitboxes))
		return Car::collisionSide::Left;

	car->getBoolIsCollision(Car::collisionSide::Left) = false;

	if (checkCollisionWithOneHitbox(rightHitboxes))
		return Car::collisionSide::Right;

	car->getBoolIsCollision(Car::collisionSide::Right) = false;

	if (checkCollisionWithOneHitbox(upRightHitboxes))
		return Car::collisionSide::RightUp;

	car->getBoolIsCollision(Car::collisionSide::Right) = false;

	if (checkCollisionWithOneHitbox(upLeftHitboxes))
		return Car::collisionSide::LeftUp;

	car->getBoolIsCollision(Car::collisionSide::Left) = false;

	if (checkCollisionWithOneHitbox(downRightHitboxes))
		return Car::collisionSide::RightDown;

	car->getBoolIsCollision(Car::collisionSide::Right) = false;

	if (checkCollisionWithOneHitbox(downLeftHitboxes))
		return Car::collisionSide::LeftDown;

	car->getBoolIsCollision(Car::collisionSide::Left) = false;

	return Car::collisionSide::None;
}

bool Collision::checkCollisionWithOneHitbox(const std::vector<sf::CircleShape*>& hitbox)
{
	for (const auto &i : hitbox)
		if (collisionArea->getPixel(static_cast<unsigned int>(i->getGlobalBounds().left + i->getGlobalBounds().width / 2),
			static_cast<unsigned int>(i->getGlobalBounds().top + i->getGlobalBounds().height / 2)) == sf::Color(255, 0, 0))
			return true;

	return false;
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
	while (checkCollisionWithOneHitbox(hitbox))
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
	while (checkCollisionWithOneHitbox(hitbox))
	{
		switch (side)
		{
		case Car::collisionSide::Right:
		case Car::collisionSide::RightDown:
		case Car::collisionSide::RightUp:
			w = car->getMovementVector(std::fmod(car->getShape()->getShape()->getRotation() - static_cast<float>(*car->getOverSteerValue()) - 90, 360.f));
			break;
		case Car::collisionSide::LeftDown:
		case Car::collisionSide::LeftUp:
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
