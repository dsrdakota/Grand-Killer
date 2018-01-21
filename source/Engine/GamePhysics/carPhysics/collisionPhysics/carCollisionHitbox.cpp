#include "carCollisionHitbox.hpp"

#include "../../../../Manager/renderSprites.hpp"

#include <fstream>

carCollisionHitbox::carCollisionHitbox(Car *car)
{
	this->car = car;

	lastCollisionSide = Car::collisionSide::None;

	std::string pathToHitboxFile="data/Models/Cars/";

	switch (*car->getType())
	{
	case carType::Type::Ambulance:
		break;
	case carType::Type::Audi:
		break;
	case carType::Type::Black_viper:
		break;
	case carType::Type::Car:
		break;
	case carType::Type::Mini_truck:
		break;
	case carType::Type::Mini_van:
		break;
	case carType::Type::Police:
		break;
	case carType::Type::Taxi:

		pathToHitboxFile += "Taxi/taxi.gk";

		break;
	case carType::Type::Truck:
		break;
	}

	std::ifstream file(pathToHitboxFile, std::ios::binary);

	unsigned count;
	sf::Vector2f position;
	unsigned side;

	file.read((char*)&count, sizeof(count));

	for (size_t i = 0;i < count;++i)
	{
		file.read((char*)&position.x, sizeof(position.x));
		file.read((char*)&position.y, sizeof(position.y));
		file.read((char*)&side, sizeof(side));

		sf::CircleShape *hitbox = new sf::CircleShape(1);
		hitbox->setOrigin(car->getSprite()->getOrigin() - position);
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

std::vector<sf::CircleShape*> carCollisionHitbox::getOneCollisionHitbox(const Car::hitboxPosition & pos)
{
	return allHitboxInOneVector[static_cast<int>(pos)];
}

Car::collisionSide *carCollisionHitbox::getLastCollisionSide()
{
	return &lastCollisionSide;
}

const std::vector<sf::CircleShape*> carCollisionHitbox::getAllHitboxes()
{
	return allHitboxes;
}

void carCollisionHitbox::update()
{
	for (const auto &i : allHitboxes)
	{
		i->setRotation(car->getSprite()->getRotation());
		i->setPosition(car->getSprite()->getPosition());
	}
}

void carCollisionHitbox::draw()
{
	for (const auto &i : allHitboxes)
		renderSprites::Instance().addToRender(i);
}
