#include "Door.hpp"

#include "Car.hpp"
#include "../../Manager/renderSprites.hpp"

Door::Door(const sf::Sprite *sprite, const carType::Type &type)
{
	car = sprite;

	underDoors = new sf::RectangleShape;
	underDoors->setFillColor(sf::Color::Black);

	doorsHitbox = new sf::CircleShape[4];
	doors = new sf::RectangleShape[4];

	std::string pathToTexture = "data/Models/Cars/";

	switch (type)
	{
	case carType::Type::Ambulance:
		break;
	case carType::Type::Audi:

		underDoors->setSize(sf::Vector2f(78, 130));
		underDoors->setOrigin(sprite->getOrigin().x - 10, sprite->getOrigin().y - 40);

		pathToTexture += "Audi/doors/";

		doorsHitbox[0].setOrigin(sprite->getOrigin().x - 14.5f, sprite->getOrigin().y - 71);
		doorsHitbox[1].setOrigin(sprite->getOrigin().x - 14, sprite->getOrigin().y - 122);
		doorsHitbox[2].setOrigin(sprite->getOrigin().x - 80.5f, sprite->getOrigin().y - 69);
		doorsHitbox[3].setOrigin(sprite->getOrigin().x - 77.5f, sprite->getOrigin().y - 122);

		doors[0].setSize(sf::Vector2f(8.5f, 49));
		doors[1].setSize(sf::Vector2f(8, 52));
		doors[2].setSize(sf::Vector2f(7.5f, 52));
		doors[3].setSize(sf::Vector2f(8, 49));

		doors[0].setOrigin(3, 3);
		doors[1].setOrigin(1, 1);
		doors[2].setOrigin(5, 4);
		doors[3].setOrigin(3, 1);

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

		underDoors->setSize(sf::Vector2f(78, 120));
		underDoors->setOrigin(sprite->getOrigin().x - 2, sprite->getOrigin().y - 35);

		pathToTexture += "Taxi/doors/";

		doorsHitbox[0].setOrigin(sprite->getOrigin().x - 3, sprite->getOrigin().y - 62);
		doorsHitbox[1].setOrigin(sprite->getOrigin().x - 3, sprite->getOrigin().y - 107);
		doorsHitbox[2].setOrigin(sprite->getOrigin().x - 77, sprite->getOrigin().y - 59);
		doorsHitbox[3].setOrigin(sprite->getOrigin().x - 77, sprite->getOrigin().y - 108);

		doors[0].setSize(sf::Vector2f(9, 44));
		doors[1].setSize(sf::Vector2f(8, 49));
		doors[2].setSize(sf::Vector2f(8, 49));
		doors[3].setSize(sf::Vector2f(7, 41));

		doors[0].setOrigin(1, 1);
		doors[1].setOrigin(1, 1);
		doors[2].setOrigin(6, 0);
		doors[3].setOrigin(6, 0);

		break;
	case carType::Type::Truck:
		break;
	}

	doorTextures = new sf::Texture[4];
	doorTextures[0].loadFromFile(pathToTexture + "leftF.png");
	doorTextures[1].loadFromFile(pathToTexture + "leftB.png");
	doorTextures[2].loadFromFile(pathToTexture + "rightF.png");
	doorTextures[3].loadFromFile(pathToTexture + "rightB.png");

	for (size_t i = 0;i < 4;++i)
	{
		doorTextures[i].setSmooth(true);
		doors[i].setTexture(dynamic_cast<const sf::Texture*>(&doorTextures[i]));
	}

	for (size_t i = 0;i < 4;++i)
	{
		doorsHitbox[i].setRadius(1);
		doorsHitbox[i].setFillColor(sf::Color::Red);
	}

	angleOpen = new float[4]{ 0 };
	MAX_ANGLEN_OPEN = new const float(65.f);

	updatePosition();
}

Door::~Door()
{
	delete[]doors;
	delete[]doorTextures;
	delete[]doorsHitbox;
	delete underDoors;
}

void Door::toControl()
{
	updatePosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		open(doorSide::leftFront, 1);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		close(doorSide::leftFront, -1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		open(doorSide::rightFront, -1);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		close(doorSide::rightFront, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		open(doorSide::leftBack, 1);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		close(doorSide::leftBack, -1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		open(doorSide::rightBack, -1);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		close(doorSide::rightBack, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		open(doorSide::leftFront, 1);
		open(doorSide::rightFront, -1);
		open(doorSide::leftBack, 1);
		open(doorSide::rightBack, -1);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		close(doorSide::leftFront, -1);
		close(doorSide::rightFront, 1);
		close(doorSide::leftBack, -1);
		close(doorSide::rightBack, 1);
	}
}

void Door::move(const sf::Vector2f & offset)
{
	underDoors->move(offset);

	for (size_t i = 0;i < 4;++i)
		doorsHitbox[i].move(offset);
	updatePosition();
}

void Door::rotate(const float & angle)
{
	underDoors->rotate(angle);

	for (size_t i = 0;i < 4;++i)
	{
		doorsHitbox[i].rotate(angle);
		doors[i].rotate(angle);
	}
	updatePosition();
}

void Door::setRotation(const float & rotation)
{
	underDoors->setRotation(rotation);

	for (size_t i = 0;i < 4;++i)
		doorsHitbox[i].setRotation(rotation);
	updatePosition();
}

void Door::open(const doorSide & side, const float &angle)
{
	if (angleOpen[static_cast<int>(side)] < *MAX_ANGLEN_OPEN)
	{
		doors[static_cast<int>(side)].rotate(angle);
		doors[static_cast<int>(side)].setSize(sf::Vector2f(doors[static_cast<int>(side)].getSize().x - 0.07f,
			doors[static_cast<int>(side)].getSize().y));
		angleOpen[static_cast<int>(side)] += fabs(angle);
	}
}

void Door::close(const doorSide & side, const float &angle)
{
	if (angleOpen[static_cast<int>(side)] > 0.f)
	{
		doors[static_cast<int>(side)].rotate(angle);
		doors[static_cast<int>(side)].setSize(sf::Vector2f(doors[static_cast<int>(side)].getSize().x + 0.07f,
			doors[static_cast<int>(side)].getSize().y));
		angleOpen[static_cast<int>(side)] -= fabs(angle);
	}
}

void Door::drawCenter()
{
	renderSprites::Instance().addToRender(underDoors);
}

void Door::drawDoors()
{
	for (size_t i = 0;i < 4;++i)
		renderSprites::Instance().addToRender(&doors[i]);
}

void Door::updatePosition()
{
	underDoors->setPosition(car->getPosition());
	underDoors->setRotation(car->getRotation());

	for (size_t i = 0;i < 4;++i)
	{
		doorsHitbox[i].setPosition(car->getPosition());
		doorsHitbox[i].setRotation(car->getRotation());
	}

	for (size_t i = 0;i < 4;++i)
	{
		doors[i].setPosition(doorsHitbox[i].getGlobalBounds().left + doorsHitbox[i].getGlobalBounds().width / 2,
			doorsHitbox[i].getGlobalBounds().top + doorsHitbox[i].getGlobalBounds().height / 2);
	}
}
