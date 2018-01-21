#include "Car.hpp"
#include "../../Manager/Texture.hpp"
#include "../../Manager/renderSprites.hpp"
#include "../GamePhysics/carPhysics/carPhysics.hpp"
#include "../GamePhysics/carPhysics/collisionPhysics/carCollisionHitbox.hpp"

Car::Car(const carType::Type &type, const sf::Vector2f &startPos) : window(Game::Instance().getWindow())
{
	this->type = new carType::Type(type);

	std::string pathToTexture = "data/Models/Cars/";
	std::string pathToShadow = "data/Models/Cars/";
	std::string nameTexture;
	sf::Vector2f origin;

	switch (type)
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

		weight = new unsigned(1500);

		origin = sf::Vector2f(41,99);

		pathToTexture += "Taxi/taxi.png";
		pathToShadow += "Taxi/taxiShadow.png";
		nameTexture = "Taxi";

		break;
	case carType::Type::Truck:
		break;
	}

	sprite = new sf::Sprite(*textureManager::load(nameTexture, pathToTexture));
	sprite->setPosition(startPos);
	sprite->setOrigin(origin);

	tire = new Tire(this, type);
	door = new Door(sprite, type);

	tire->setPosition(sprite, type);

	for (auto &i : isCollision)
		i = false;

	physics = new carPhysics(this);
}

Car::~Car()
{
	delete sprite;
	delete door;
	delete tire;
	delete weight;

	delete physics; // kappa
}

double Car::getSpeed()
{
	return *physics->getPhysicsMove()->getSpeed();
}

void Car::setSpeed(const float &speed)
{
	physics->getPhysicsMove()->setSpeed(speed);
}

sf::Vector2f Car::getMovementVector(const float &rot)
{
	if(rot == 361) return physics->getPhysicsMove()->getMovementVector(sprite->getRotation() - static_cast<float>(*getOverSteerValue()));
	return physics->getPhysicsMove()->getMovementVector(rot);
}

const double Car::getMaxSpeed()
{
	return *physics->getPhysicsMove()->getMaxSpeed();
}

const double * Car::getOverSteerValue()
{
	return physics->getPhysicsTurn()->getOverSteerValue();
}

const int Car::getOverSteerSide()
{
	return physics->getPhysicsTurn()->getSlidePhycics()->getOverSteerSide();
}

double * Car::getBreakingForceOfSlide()
{
	return physics->getPhysicsTurn()->getSlidePhycics()->getBreakingForceOfSlide();
}

int Car::getTypeOfDrive()
{
	return physics->getPhysicsMove()->getTypeOfDrive();
}

int Car::getStateMoving()
{
	return physics->getPhysicsMove()->getStateMoving();
}

bool Car::isSlide()
{
	return physics->getPhysicsTurn()->isSlide();
}

void Car::breakSlide()
{
	physics->getPhysicsTurn()->breakSlide();
}

bool & Car::getBoolIsCollision(const Car::collisionSide &side)
{	
	return isCollision[static_cast<int>(side)];
}

const std::vector<sf::CircleShape*> Car::getCollisionHitbox(const hitboxPosition & pos)
{
	return physics->getCollisionHitboxes()->getOneCollisionHitbox(pos);
}

Car::collisionSide *Car::getLastCollisionSide()
{
	return physics->getCollisionHitboxes()->getLastCollisionSide();
}

const std::vector<sf::CircleShape*> Car::getAllHitboxes()
{
	return physics->getCollisionHitboxes()->getAllHitboxes();
}

void Car::toControl()
{
	updatePosition();

	// ----- Main control

	turnLeft(sf::Keyboard::A);
	turnRight(sf::Keyboard::D);

	gas(sf::Keyboard::W);
	brake(sf::Keyboard::S);

	handBrake(sf::Keyboard::Space);

	door->toControl();
}

float Car::getRotation()
{
	return static_cast<float>(sprite->getRotation() - *getOverSteerValue());
}

sf::Vector2f Car::getPosition()
{
	return sf::Vector2f(sprite->getPosition());
}

void Car::setPhycics(Car *car)
{
	physics = new carPhysics(car);
}

void Car::move(const sf::Vector2f & offset)
{
	sprite->move(offset);
	door->move(offset);
	tire->move(offset);
}

void Car::rotate(const double & angle)
{
	sprite->rotate(static_cast<float>(angle));
	door->rotate(static_cast<float>(angle));
	tire->rotate(angle);
}

void Car::updatePosition()
{
	physics->updatePosition();
}

void Car::draw()
{
	// float rect sprite outside view
	if (!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top)) ||
		!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top)) ||
		!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)) ||
		!Map::isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)))
	{
		tire->draw();

		door->drawCenter();

		renderSprites::Instance().addToRender(sprite);

		door->drawDoors();

		//physics->draw();
	}
}

void Car::gas(const sf::Keyboard::Key & key)
{
	physics->boostSpeed(key);
}

void Car::brake(const sf::Keyboard::Key & key)
{
	physics->reduceSpeed(key);
}

void Car::handBrake(const sf::Keyboard::Key & key)
{
	physics->handBrake(key);
}

void Car::turnLeft(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key))
		physics->turn(toTurn::Direction::Left);
	else
		*physics->getPhysicsTurn()->getStatusKeyToTurn(toTurn::Direction::Left) = toTurn::keyStatus::Released;
}

void Car::turnRight(const sf::Keyboard::Key & key)
{
	if (sf::Keyboard::isKeyPressed(key))
		physics->turn(toTurn::Direction::Right);
	else
		*physics->getPhysicsTurn()->getStatusKeyToTurn(toTurn::Direction::Right) = toTurn::keyStatus::Released;
}