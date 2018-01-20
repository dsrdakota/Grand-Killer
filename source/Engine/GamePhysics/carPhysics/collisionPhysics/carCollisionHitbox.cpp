#include "carCollisionHitbox.hpp"

#include "../../../../Manager/renderSprites.hpp"

carCollisionHitbox::carCollisionHitbox(Car *car)
{
	this->car = car;

	lastCollisionSide = Car::collisionSide::None;

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

		

		break;
	case carType::Type::Truck:
		break;
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
