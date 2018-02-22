#include "Car.hpp"
#include "../../Manager/Texture.hpp"
#include "../../Manager/renderSprites.hpp"
#include "../GamePhysics/carPhysics/carPhysics.hpp"

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

		weight = new unsigned(1500);

		origin = sf::Vector2f(48, 111);

		pathToTexture += "Audi/audi.png";
		pathToShadow += "Audi/audi_shadow.png";
		nameTexture = "Audi";

		shadow = new sf::Sprite(*textureManager::load(nameTexture + "Shadow", pathToShadow));
		shadow->setPosition(startPos.x + 40, startPos.y);
		shadow->setOrigin(83, 128);

		break;
	case carType::Type::Black_viper:

		weight = new unsigned(1750);

		origin = sf::Vector2f(44, 111);

		pathToTexture += "Black_viper/black_viper.png";
		pathToShadow += "Black_viper/black_viper_shadow.png";
		nameTexture = "Black_viper";

		shadow = new sf::Sprite(*textureManager::load(nameTexture + "Shadow", pathToShadow));
		shadow->setPosition(startPos.x + 40, startPos.y);
		shadow->setOrigin(79, 128);

		break;
	case carType::Type::Car:

		weight = new unsigned(2200);

		origin = sf::Vector2f(42, 105);

		pathToTexture += "Car/car.png";
		pathToShadow += "Car/car_shadow.png";
		nameTexture = "Car";

		shadow = new sf::Sprite(*textureManager::load(nameTexture + "Shadow", pathToShadow));
		shadow->setPosition(startPos.x + 40, startPos.y);
		shadow->setOrigin(77, 122);

		break;
	case carType::Type::Mini_truck:

		weight = new unsigned(3000);

		origin = sf::Vector2f(54, 116);

		pathToTexture += "Mini_truck/mini_truck.png";
		pathToShadow += "Mini_truck/mini_truck_shadow.png";
		nameTexture = "Mini_truck";

		shadow = new sf::Sprite(*textureManager::load(nameTexture + "Shadow", pathToShadow));
		shadow->setPosition(startPos.x + 40, startPos.y);
		shadow->setOrigin(79, 122);

		break;
	case carType::Type::Mini_van:
		break;
	case carType::Type::Police:

		weight = new unsigned(1850);

		origin = sf::Vector2f(45, 110);

		pathToTexture += "Police/police.png";
		pathToShadow += "Police/police_shadow.png";
		nameTexture = "Police";

		shadow = new sf::Sprite(*textureManager::load(nameTexture + "Shadow", pathToShadow));
		shadow->setPosition(startPos.x + 40, startPos.y);
		shadow->setOrigin(80, 129);

		break;
	case carType::Type::Taxi:

		weight = new unsigned(2000);

		origin = sf::Vector2f(41,99);

		pathToTexture += "Taxi/taxi.png";
		pathToShadow += "Taxi/taxi_shadow.png";
		nameTexture = "Taxi";

		shadow = new sf::Sprite(*textureManager::load(nameTexture + "Shadow", pathToShadow));
		shadow->setPosition(startPos.x + 20, startPos.y);
		shadow->setOrigin(81, 129);

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

unsigned Car::getWeight()
{
	return *weight;
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

sf::FloatRect Car::getGlobalBounds()
{
	auto &boundingBox = sprite->getGlobalBounds();
	return sf::FloatRect(sf::Vector2f(boundingBox.left - 10.f, boundingBox.top - 10.f),
		sf::Vector2f(boundingBox.width + 10.f, boundingBox.height + 10.f));
}

void Car::setPowerOfCrashMove(const std::pair<sf::Vector2f, float> &power)
{
	physics->getPhysicsMove()->setPowerOfCrashMove(power);
}

void Car::setPowerOfCrashRotate(const std::pair<float, float>&power)
{
	physics->getPhysicsMove()->setPowerOfCrashRotate(power);
}

bool Car::isRotateAble()
{
	return physics->getPhysicsMove()->isRotateAble();
}

bool Car::isMoveAble()
{
	return physics->getPhysicsMove()->isMoveAble();
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
	return sprite->getRotation();
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
	shadow->move(offset);
	door->move(offset);
	tire->move(offset);
}

void Car::rotate(const double & angle)
{
	sprite->rotate(static_cast<float>(angle));
	shadow->rotate(static_cast<float>(angle));
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
	if (!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left, shadow->getGlobalBounds().top)) ||
		!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left + shadow->getGlobalBounds().width, shadow->getGlobalBounds().top)) ||
		!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left + shadow->getGlobalBounds().width, shadow->getGlobalBounds().top + shadow->getGlobalBounds().height)) ||
		!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left, shadow->getGlobalBounds().top + shadow->getGlobalBounds().height)))
	{
		door->drawCenter();

		renderSprites::Instance().addToRender(sprite);

		door->drawDoors();

		physics->draw();
	}
}

void Car::drawShadow()
{
	if (!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left, shadow->getGlobalBounds().top)) ||
		!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left + shadow->getGlobalBounds().width, shadow->getGlobalBounds().top)) ||
		!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left + shadow->getGlobalBounds().width, shadow->getGlobalBounds().top + shadow->getGlobalBounds().height)) ||
		!Map::isOutsideView(sf::Vector2f(shadow->getGlobalBounds().left, shadow->getGlobalBounds().top + shadow->getGlobalBounds().height)))
	{
		renderSprites::Instance().addToRender(shadow);
		tire->draw();
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