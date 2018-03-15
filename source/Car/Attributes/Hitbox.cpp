#include "Hitbox.hpp"

#include "../Car.hpp"

#include "../../Engine/Engine.hpp"

#include <fstream>

Hitbox::Hitbox(const std::string &carName)
{
	allHitboxes = CarConfig::getHitboxes(carName);
	allHitboxInOneVector = CarConfig::getHitboxVectors(carName);
	spliteToVectors();
}

bool & Hitbox::getBoolIsCollision(const collisionSide & side)
{
	return isCollision[static_cast<int>(side)];
}

std::vector<sf::CircleShape*> Hitbox::getCollisionHitbox(const hitboxPosition & pos)
{
	return allHitboxInOneVector[static_cast<int>(pos)];
}

Hitbox::collisionSide *Hitbox::getLastCollisionSide()
{
	return &lastCollisionSide;
}

const std::vector<sf::CircleShape*> Hitbox::getAllHitboxes()
{
	return allHitboxes;
}

void Hitbox::moveHitboxes(const sf::Vector2f & offset)
{
	for (const auto &i : allHitboxes)
		i->move(offset);
}

void Hitbox::rotateHitboxes(const double & angle)
{
	for (const auto &i : allHitboxes)
		i->rotate(static_cast<float>(angle));
}

void Hitbox::rotateOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const float & angle)
{
	for (const auto &i : hitbox)
		i->rotate(angle);
}

void Hitbox::moveOneHitbox(const std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & offset)
{
	for (const auto &i : hitbox)
		i->move(offset);
}

sf::Vector2f Hitbox::getCenterOfHitbox(const sf::CircleShape & hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}

void Hitbox::update()
{
	for (const auto &i : allHitboxes)
	{
		i->setRotation(sprite->getRotation());
		i->setPosition(sprite->getPosition());
	}
}

void Hitbox::draw()
{
	//for (const auto &i : allHitboxes)
		//renderSprites::Instance().addToRender(i);
}

void Hitbox::spliteToVectors()
{
	frontHitboxes = allHitboxInOneVector[0];
	upRightHitboxes = allHitboxInOneVector[1];
	rightHitboxes = allHitboxInOneVector[2];
	downRightHitboxes = allHitboxInOneVector[3];
	backHitboxes = allHitboxInOneVector[4];
	downLeftHitboxes = allHitboxInOneVector[5];
	leftHitboxes = allHitboxInOneVector[6];
	upLeftHitboxes = allHitboxInOneVector[7];
}
