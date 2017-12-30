#include "Collision.hpp"

#include "../../Manager/renderSprites.hpp"

#include <iostream>

Collision::Collision(Car * car)
{
	this->car = car;

	auto allHitboxes = car->getAllHitboxes();

	collsisionArea = Map::Instance().getCollisionHitbox();

	setHitbox(upRightHitboxes, sf::Vector2f(15, 80), sf::Color::Green);
	setHitbox(rightHitboxes, sf::Vector2f(81, 190), sf::Color::Blue);
	setHitbox(downRightHitboxes, sf::Vector2f(191, 250), sf::Color::Red);
	setHitbox(downHitboxes, sf::Vector2f(251, 300), sf::Color::Yellow);
	setHitbox(downLeftHitboxes, sf::Vector2f(301, 360), sf::Color::Magenta);
	setHitbox(leftHitboxes, sf::Vector2f(361, 460), sf::Color(83, 47, 40));
	setHitbox(upLeftHitboxes, sf::Vector2f(461, 523), sf::Color(255, 165, 0));
	setHitbox(upLeftHitboxes, sf::Vector2f(allHitboxes.size() - 10, allHitboxes.size()-1), sf::Color(255, 165, 0));
	setHitbox(upHitboxes, sf::Vector2f(524, allHitboxes.size()-11), sf::Color(75, 0, 130));
	setHitbox(upHitboxes, sf::Vector2f(0, 14), sf::Color(75, 0, 130));
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
		{
			car->setSpeed(0);
			car->getBoolIsCollision(collisionSide) = true;
		}

		break;
	case Car::collisionSide::Back:

		if (car->getStateMoving() == 1) // back
		{
			car->setSpeed(0);
			car->getBoolIsCollision(collisionSide) = true;
		}

		break;
	case Car::collisionSide::Left:
		break;
	case Car::collisionSide::Right:
		break;
	}
}

void Collision::draw()
{
	for (const auto &i : upRightHitboxes)
		renderSprites::Instance().addToRender(i.first);

	for (const auto &i : rightHitboxes)
		renderSprites::Instance().addToRender(i.first);

	for (const auto &i : downRightHitboxes)
		renderSprites::Instance().addToRender(i.first);

	for (const auto &i : downHitboxes)
		renderSprites::Instance().addToRender(i.first);

	for (const auto &i : downLeftHitboxes)
		renderSprites::Instance().addToRender(i.first);

	for (const auto &i : leftHitboxes)
		renderSprites::Instance().addToRender(i.first);

	for (const auto &i : upLeftHitboxes)
		renderSprites::Instance().addToRender(i.first);

	for (const auto &i : upHitboxes)
		renderSprites::Instance().addToRender(i.first);
}

void Collision::setHitbox(std::vector<std::pair<sf::CircleShape*, unsigned int>>& hitbox, const sf::Vector2f & range, const sf::Color & color)
{
	auto allHitboxes = car->getAllHitboxes();

	for (size_t i = static_cast<size_t>(range.x);i <= static_cast<size_t>(range.y);i++)
	{
		hitbox.push_back(std::make_pair(allHitboxes[i],i));
		hitbox[hitbox.size() - 1].first->setFillColor(color);
	}
}

Car::collisionSide Collision::whereIsCollision()
{
	for (const auto &i : upHitboxes)
		if (collsisionArea->getPixel(i.first->getGlobalBounds().left + i.first->getGlobalBounds().width / 2,
			i.first->getGlobalBounds().top + i.first->getGlobalBounds().height / 2) == sf::Color(255, 0, 0))

			return Car::collisionSide::Front;

	car->getBoolIsCollision(Car::collisionSide::Front) = false;

	for (const auto &i : downHitboxes)
		if (collsisionArea->getPixel(i.first->getGlobalBounds().left + i.first->getGlobalBounds().width / 2,
			i.first->getGlobalBounds().top + i.first->getGlobalBounds().height / 2) == sf::Color(255, 0, 0))

			return Car::collisionSide::Back;

	car->getBoolIsCollision(Car::collisionSide::Back) = false;

	return Car::collisionSide::None;
}
