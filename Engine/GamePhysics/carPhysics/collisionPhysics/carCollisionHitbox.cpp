#include "carCollisionHitbox.hpp"

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

		setHitbox(frontHitboxes, sf::Vector2f(1, 3), sf::Color(75, 0, 130));
		setHitbox(upRightHitboxes, sf::Vector2f(4, 9), sf::Color::Green);
		setHitbox(rightHitboxes, sf::Vector2f(10, 13), sf::Color::Blue);
		setHitbox(downRightHitboxes, sf::Vector2f(14, 19), sf::Color::Red);
		setHitbox(backHitboxes, sf::Vector2f(20, 23), sf::Color::Yellow);
		setHitbox(downLeftHitboxes, sf::Vector2f(24, 28), sf::Color::Magenta);
		setHitbox(leftHitboxes, sf::Vector2f(29, 33), sf::Color(83, 47, 40));
		setHitbox(upLeftHitboxes, sf::Vector2f(34, static_cast<float>(car->getAllHitboxes().size()-1)), sf::Color(255, 165, 0));
		setHitbox(upLeftHitboxes, sf::Vector2f(0,0), sf::Color(255, 165, 0));

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

void carCollisionHitbox::setHitbox(std::vector<sf::CircleShape*>& hitbox, const sf::Vector2f & range, const sf::Color & color)
{
	auto allHitboxes = car->getAllHitboxes();

	for (size_t i = static_cast<size_t>(range.x);i <= static_cast<size_t>(range.y);i++)
	{
		hitbox.push_back(allHitboxes[i]);
		hitbox[hitbox.size() - 1]->setFillColor(color);
	}
}
