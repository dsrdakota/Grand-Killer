#include "Tire.hpp"
#include "../../Manager/Texture.hpp"
#include "../../Manager/renderSprites.hpp"
#include "Car.hpp"

Tire::Tire(Car *car,const carType::Type &type)
{
	tires = new sf::Sprite[4];
	tiresPos = new sf::CircleShape[4];

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
		tires[i].setTexture(*textureManager::load(nameTexture + std::to_string(i), pathToTexture));

	traces = new Traces(car,tiresPos);
}

Tire::~Tire()
{
	delete[]tires;
	delete[]tiresPos;
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

		tiresPos[0].setOrigin(car->getOrigin().x, car->getOrigin().y - 30);
		tiresPos[1].setOrigin(car->getOrigin().x - 71.f, car->getOrigin().y - 30);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x, car->getOrigin().y - 140);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x, car->getOrigin().y - 140);

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

void Tire::move(const sf::Vector2f & offset)
{
	for (int i = 0;i < 4;++i)
	{
		tires[i].move(offset);
		tiresPos[i].move(offset);
	}
}

void Tire::rotate(const double & angle, const sf::ConvexShape *car)
{
	for (int i = 0;i < 4;++i)
	{
		tires[i].rotate(static_cast<float>(angle));
		tiresPos[i].rotate(static_cast<float>(angle));

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
	}
}

void Tire::draw()
{
	traces->setTraces();
	traces->draw();

	for (auto i = 0;i < 4;++i)
		renderSprites::Instance().addToRender(tires + i);
}