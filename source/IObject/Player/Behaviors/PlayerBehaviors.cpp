#include "PlayerBehaviors.hpp"

#include "../../../Car/Car.hpp"

PlayerBehaviors::PlayerBehaviors()
{
	carName = new Text(sf::Color::White, 50, "", "italic");
	timeShowingName = new Time;
}

PlayerBehaviors::~PlayerBehaviors()
{
	delete carName;
	delete timeShowingName;
}

void PlayerBehaviors::controlBody()
{
}

void PlayerBehaviors::controlCar()
{
	if (!sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Break)) && sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Gas)))
		car->gas();

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Break)))
		car->brake();

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::HandBreak)))
		car->handBrake();

	if (!sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Break)) && !sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::Gas)))
		car->slack();

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::TurnLeft)))
		car->getToTurnClass()->turning(ToTurn::Direction::Left);
	else
		stateKeyLeftTurn = false;

	if (sf::Keyboard::isKeyPressed(GlobalSteerage::getKey(GlobalSteerage::Sections::Car, GlobalSteerage::Type::TurnRight)))
		car->getToTurnClass()->turning(ToTurn::Direction::Right);
	else
		stateKeyRightTurn = false;

	car->getToTurnClass()->updatePosition();
	updateCarName();
}

void PlayerBehaviors::showCarName()
{
	carName->text->setString(car->getName());

	carName->text->setPosition(static_cast<float>(GlobalSettings::getWidth()) - carName->text->getGlobalBounds().width - 40,
		static_cast<float>(GlobalSettings::getHeight() - carName->text->getGlobalBounds().height - 40));

	timeShowingName->clock->restart();
	*timeShowingName->time = sf::Time::Zero;
}

void PlayerBehaviors::updateCarName()
{
	if (timeShowingName->time->asSeconds() < 2)
		Painter::Instance().addToInterfaceDraw(carName->text);
}
