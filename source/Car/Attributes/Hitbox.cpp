#include "Hitbox.hpp"

#include "../Car.hpp"

#include "../../Engine/Engine.hpp"

#include <fstream>

Hitbox::Hitbox(Car *car)
{
	this->sprite = car->getSprite();

	for (auto &i : isCollision)
		i = false;

	std::string lowerCarName = car->getName();
	std::transform(lowerCarName.begin(), lowerCarName.end(), lowerCarName.begin(), ::tolower);
	std::ifstream file("data/Models/Cars/" + car->getName() + '/' + lowerCarName + ".hitbox", std::ios::binary);

	unsigned count;
	sf::Vector2f position;
	unsigned side;

	file.read((char*)&count, sizeof(count));

	for (size_t i = 0;i < count;++i)
	{
		file.read((char*)&position.x, sizeof(position.x));
		file.read((char*)&position.y, sizeof(position.y));
		file.read((char*)&side, sizeof(side));

		sf::CircleShape *hitbox = new sf::CircleShape(2);
		hitbox->setOrigin(car->getSprite()->getOrigin() - position + sf::Vector2f(hitbox->getRadius(), hitbox->getRadius()));
		hitbox->setPosition(car->getSprite()->getPosition());

		allHitboxes.push_back(hitbox);

		switch (side)
		{
		case 0:
			frontHitboxes.push_back(hitbox);
			break;
		case 1:
			upRightHitboxes.push_back(hitbox);
			break;
		case 2:
			rightHitboxes.push_back(hitbox);
			break;
		case 3:
			downRightHitboxes.push_back(hitbox);
			break;
		case 4:
			backHitboxes.push_back(hitbox);
			break;
		case 5:
			downLeftHitboxes.push_back(hitbox);
			break;
		case 6:
			leftHitboxes.push_back(hitbox);
			break;
		case 7:
			upLeftHitboxes.push_back(hitbox);
			break;
		}
	}

	allHitboxInOneVector.push_back(frontHitboxes);
	allHitboxInOneVector.push_back(upRightHitboxes);
	allHitboxInOneVector.push_back(rightHitboxes);
	allHitboxInOneVector.push_back(downRightHitboxes);
	allHitboxInOneVector.push_back(backHitboxes);
	allHitboxInOneVector.push_back(downLeftHitboxes);
	allHitboxInOneVector.push_back(leftHitboxes);
	allHitboxInOneVector.push_back(upLeftHitboxes);
}

Hitbox::~Hitbox()
{
	for (auto &i : allHitboxes)
		delete i;
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
		//Painter::Instance().addToDraw(i);
}
