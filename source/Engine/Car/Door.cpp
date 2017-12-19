#include "Door.hpp"
#include "../../Manager/renderSprites.hpp"

#include <iostream>
#include <string>
#include <fstream>

Door::Door(const carType::Type &type)
{
	this->type = new carType::Type(type);
	doors = new Shape[4];
	center = new Shape[4];

	angleOpen = new float[4];
	angleClose = new float[4];

	std::fill(angleOpen, angleOpen + 4, 0.f);
	std::fill(angleClose, angleClose + 4, 0.f);

	std::string pathToShape = "data/Models/Cars/";
	std::string pathToTexture = pathToShape;
	std::string nameTexture;

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

		pathToShape += "Taxi/doors/";
		pathToTexture += "Taxi/doors/";
		nameTexture = "TaxiDoor";

		break;
	case carType::Type::Truck:
		break;
	}

	setPath(pathToShape, pathToTexture, "FrontL", nameTexture, 0);

	setPath(pathToShape, pathToTexture, "FrontR", nameTexture, 1);

	setPath(pathToShape, pathToTexture, "BackL", nameTexture, 2);

	setPath(pathToShape, pathToTexture, "BackR", nameTexture, 3);
}

Door::~Door()
{
	delete type;
	delete[]doors;
	delete[]angleOpen;
	delete[]angleClose;
}

void Door::setPosition(const sf::ConvexShape * car, const carType::Type &type)
{
	
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

		doors[0].setOrigin(car->getOrigin().x - 68.5f, car->getOrigin().y - 72);
		center[0].setOrigin(doors[0].getOrigin());

		doors[1].setOrigin(car->getOrigin().x - 135.5f, car->getOrigin().y - 71);
		center[1].setOrigin(doors[1].getOrigin());

		doors[2].setOrigin(car->getOrigin().x - 68.5012f, car->getOrigin().y - 114);
		center[2].setOrigin(doors[2].getOrigin());

		doors[3].setOrigin(car->getOrigin().x - 136.5f, car->getOrigin().y - 118);
		center[3].setOrigin(doors[3].getOrigin());

		break;
	case carType::Type::Truck:
		break;
	}

	for (auto i = 0;i < 4;++i)
	{
		doors[i].setPosition(car->getPosition());
		center[i].setPosition(car->getPosition());

		doors[i].setRotation(car->getRotation());
		center[i].setRotation(car->getRotation());
	}
}

void Door::moveOne(const size_t & index, const sf::Vector2f & offset)
{
	doors[index].move(offset);
	center[index].move(offset);
}

void Door::move(const sf::Vector2f & offset)
{
	for (int i = 0;i < 4;++i)
	{
		doors[i].getShape()->move(offset);
		center[i].getShape()->move(offset);
	}
}

void Door::rotate(const double & angle)
{
	for (int i = 0;i < 4;++i)
	{
		doors[i].getShape()->rotate(angle);
		center[i].getShape()->rotate(angle);
	}
}

void Door::openDoor(sf::ConvexShape *door, float *angle, const size_t &index)
{
	const float *MAX_ANGLE_OPEN = nullptr;
	switch (index)
	{
		// Left Doors
	case 0: 
	case 2:
		MAX_ANGLE_OPEN = new const float(1.25f);
		break;

		// Right Doors
	case 1:
	case 3:
		MAX_ANGLE_OPEN = new const float(-1.25f);
		break;

	}
	if (*MAX_ANGLE_OPEN > 0 ? angleOpen[index] < *MAX_ANGLE_OPEN : angleOpen[index] > *MAX_ANGLE_OPEN) // wow its working
	{
		angleOpen[index] += *angle;

		rotate(door,angle,setHinge(index).first,setHinge(index).second);
	
		std::cout << angleOpen[index] << std::endl;

		if (angleOpen[index] == *MAX_ANGLE_OPEN)angleClose[index] = 0;
		else angleClose[index] = -(*MAX_ANGLE_OPEN - angleOpen[index]);
	}
}

void Door::closeDoor(sf::ConvexShape *door, float *angle, const size_t &index)
{
	const float *MAX_ANGLE_CLOSE = nullptr;
	switch (index)
	{
		// Left Doors
	case 0:
	case 2:
		MAX_ANGLE_CLOSE = new const float(-1.25f);
		break;

		// Right Doors
	case 1:
	case 3:
		MAX_ANGLE_CLOSE = new const float(1.25f);
		break;

	}
	if (*MAX_ANGLE_CLOSE < 0 ? angleClose[index] > *MAX_ANGLE_CLOSE && angleOpen[index] > 0 : angleClose[index] < *MAX_ANGLE_CLOSE && angleOpen[index] < 0) // wow its working v2
	{
		angleClose[index] -= -(*angle);
		rotate(door, angle, setHinge(index).first, setHinge(index).second);

		std::cout << angleClose[index] << std::endl;

		if (angleClose[index] == *MAX_ANGLE_CLOSE) angleOpen[index] = 0;
		else angleOpen[index] = -(*MAX_ANGLE_CLOSE - angleClose[index]);
	}
}

void Door::drawDoors()
{
	for (auto i = 0;i < 4;++i)
		renderSprites::Instance().addToRender(doors[i].getShape());
}

void Door::drawCenter()
{
	for (auto i = 0;i < 4;++i)
		renderSprites::Instance().addToRender(center[i].getShape());
}

void Door::setPath(std::string pathToShape, std::string pathToTexture, const std::string &string, const std::string &nameTexture, const int &count)
{
	pathToShape += string+".gk";
	pathToTexture += string+".png";

	doors[count].setShape(pathToShape, pathToTexture,nameTexture+std::to_string(count));
	center[count].setShape(doors[count].getShape());
}

std::pair<sf::Vector2f, size_t> Door::setHinge(const size_t &index)
{
	sf::Vector2f hinge= sf::Vector2f(0, 0);
	size_t originIndex = 0;

	switch (*type)
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

		switch (index)
		{
		case 0: // front left

			hinge = sf::Vector2f(0, 12);
			originIndex = 7;

			break;
		case 1: // front right

			hinge = sf::Vector2f(0, 20);
			originIndex = 5;

			break;
		case 2: // back left

			hinge = sf::Vector2f(0, 6);
			originIndex = 4;

			break;
		case 3: // back right

			hinge = sf::Vector2f(0, 6);
			originIndex = 4;

			break;
		}

		break;
	case carType::Type::Truck:
		break;
	}
	return std::make_pair(hinge, originIndex);
}

void Door::rotate(sf::ConvexShape *door, const float *angle, const sf::Vector2f &hinge, const size_t &originIndex)
{
	for (size_t i = 0;i < door->getPointCount();++i)
	{
		if(i >= hinge.x && i <= hinge.y)
			continue;
		door->setPoint(i, sf::Vector2f((door->getPoint(i).x - door->getPoint(originIndex).x)*cos(*angle) - (door->getPoint(i).y - door->getPoint(originIndex).y)*sin(*angle) + door->getPoint(originIndex).x,
			(door->getPoint(i).x - door->getPoint(originIndex).x)*sin(*angle) + (door->getPoint(i).y - door->getPoint(originIndex).y)*cos(*angle) + door->getPoint(originIndex).y));
	}
}
