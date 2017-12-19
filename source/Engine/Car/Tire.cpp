#include "Tire.hpp"
#include "../../Manager/Texture.hpp"
#include "../../Manager/renderSprites.hpp"
#include <iostream>
#include "Car.hpp"

Tire::Tire(Car *car,const carType::Type &type)
{
	tires = new sf::Sprite[4];
	tiresPos = new sf::CircleShape[4];
	tiresHitbox = new std::vector<sf::CircleShape*>[4];

	sf::CircleShape example(3);
	example.setOrigin(3, 3);
	std::fill(tiresPos, tiresPos + 4, example);

	std::string pathToTexture = "data/Models/Cars/";
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
		
		pathToTexture += "Taxi/tire.png";
		nameTexture = "taxiTire";

		for (auto i = 0;i < 4;++i)
			tires[i].setOrigin(5, 12);
		
		break;
	case carType::Type::Truck:
		break;
	}

	for (auto i = 0;i < 4;++i)
	{
		tires[i].setTexture(*textureManager::load(nameTexture + std::to_string(i), pathToTexture));

		for (auto j = 0;j < 6;++j)
		{
			sf::CircleShape *hitbox = new sf::CircleShape(2, 5);
			tiresHitbox[i].push_back(hitbox);
		}
	}

	traces = new Traces(car,tiresPos, tiresHitbox);
}

Tire::~Tire()
{
	delete[]tires;
	delete[]tiresPos;
}

std::pair<std::vector<sf::CircleShape*>, std::vector<sf::CircleShape*>> Tire::getPairTireHitboxFront()
{
	return std::make_pair(tiresHitbox[0],tiresHitbox[1]);
}

std::vector<sf::CircleShape*>* Tire::getVectorTireHitbox()
{
	return tiresHitbox;
}

void Tire::setPosition(const sf::ConvexShape * car, const carType::Type & type)
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

		tiresPos[0].setOrigin(car->getOrigin().x - 65, car->getOrigin().y - 40);
		tiresPos[1].setOrigin(car->getOrigin().x - 138.5f, car->getOrigin().y - 40);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x, car->getOrigin().y - 150);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x, car->getOrigin().y - 150);

		for(auto k=0;k<4;++k)
			for (auto j=68,i = 0;i < 5;i+=2,j-=5)
			{
				tiresHitbox[k][i]->setOrigin(tiresPos[0].getGlobalBounds().left + 45, tiresPos[0].getGlobalBounds().top + j);
				tiresHitbox[k][i+1]->setOrigin(tiresPos[0].getGlobalBounds().left + 38, tiresPos[0].getGlobalBounds().top + j);
			}

		break;
	case carType::Type::Truck:
		break;
	}

	for (auto i = 0;i < 4;++i)
	{
		tiresPos[i].setPosition(car->getPosition());
		tiresPos[i].setRotation(car->getRotation());

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
	}
}

void Tire::moveOne(const size_t & index, const sf::Vector2f & offset)
{
	tires[index].move(offset);
	tiresPos[index].move(offset);

	for(auto i=0;i<6;++i)
		tiresHitbox[index][i]->move(offset);
}

void Tire::move(const sf::Vector2f & offset)
{
	for (int i = 0;i < 4;++i)
	{
		tires[i].move(offset);
		tiresPos[i].move(offset);

		for (auto j = 0;j<6;++j)
			tiresHitbox[i][j]->move(offset);
	}
}

void Tire::rotate(const double & angle, const sf::ConvexShape *car)
{
	for (int i = 0;i < 4;++i)
	{
		tires[i].rotate(angle);
		tiresPos[i].rotate(angle);

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);

		for (auto j = 0;j<6;++j)
			tiresHitbox[i][j]->rotate(angle);
	}
}

void Tire::draw()
{
	updateHitboxPosition();

	traces->setTraces();
	traces->draw();

	for (auto i = 0;i < 4;++i)
	{
		renderSprites::Instance().addToRender(tires + i);
		//renderSprites::Instance().addToRender(tiresPos + i);

		//for (auto j = 0;j<6;++j)
			//renderSprites::Instance().addToRender(tiresHitbox[i][j]);
	}
}

void Tire::setRotation(sf::Sprite *target, const sf::Vector2f &posTarget, const float &angle, const sf::Vector2f &origin)
{
	//target->setPosition((posTarget.x - origin.x) * cos(angle) - (posTarget.y - origin.y) * sin(angle) + origin.x,
		//(posTarget.x - origin.x) * sin(angle) + (posTarget.y - origin.y) * cos(angle) + origin.y);
}

void Tire::updateHitboxPosition()
{	
	for(auto i=0;i<4;++i)
		for(auto j=0;j<6;++j)
			tiresHitbox[i][j]->setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
				tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
}