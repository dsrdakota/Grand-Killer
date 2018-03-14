#include "Door.hpp"

#include "../Car.hpp"

#include "../../Engine/Engine.hpp"

Door::Door(const sf::Sprite *sprite)
{
	this->sprite = sprite;

	underDoors = new sf::RectangleShape;
	underDoors->setFillColor(sf::Color::Black);

	underDoors->setRotation(sprite->getRotation());

	for (size_t i = 0;i < countDoors;++i)
	{
		doorTextures[i].setSmooth(true);
		doors[i].setTexture(dynamic_cast<const sf::Texture*>(&doorTextures[i]));
		doors[i].setRotation(sprite->getRotation());
	}

	for (size_t i = 0;i < countDoors;++i)
	{
		doorsHitbox[i].setRadius(1);
		doorsHitbox[i].setFillColor(sf::Color::Red);
	}

	angleOpen = new float[countDoors]{ 0 };
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

void Door::move(const sf::Vector2f & offset)
{
	underDoors->move(offset);

	for (size_t i = 0;i < countDoors;++i)
		doorsHitbox[i].move(offset);
	updatePosition();
}

void Door::rotate(const float & angle)
{
	underDoors->rotate(angle);

	for (size_t i = 0;i < countDoors;++i)
	{
		doorsHitbox[i].rotate(angle);
		doors[i].rotate(angle);
	}
	updatePosition();
}

void Door::setRotation(const float & rotation)
{
	underDoors->setRotation(rotation);

	for (size_t i = 0;i < countDoors;++i)
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
	Painter::Instance().addToDraw(underDoors);
}

void Door::drawDoors()
{
	for (size_t i = 0;i < countDoors;++i)
		Painter::Instance().addToDraw(&doors[i]);
}

void Door::updatePosition()
{
	underDoors->setPosition(sprite->getPosition());
	underDoors->setRotation(sprite->getRotation());

	for (size_t i = 0;i < countDoors;++i)
	{
		doorsHitbox[i].setPosition(sprite->getPosition());
		doorsHitbox[i].setRotation(sprite->getRotation());
	}

	for (size_t i = 0;i < countDoors;++i)
		doors[i].setPosition(doorsHitbox[i].getGlobalBounds().left + doorsHitbox[i].getGlobalBounds().width / 2,
			doorsHitbox[i].getGlobalBounds().top + doorsHitbox[i].getGlobalBounds().height / 2);
}
