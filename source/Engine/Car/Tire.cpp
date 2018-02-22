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

	const sf::Sprite* sprite = car->getSprite();

	switch (type)
	{
	case carType::Type::Ambulance:
		break;
	case carType::Type::Audi:

		pathToTexture += "Audi/tire.png";
		nameTexture = "audiTire";

		for (auto i = 0;i < 4;++i)
			tires[i].setOrigin(5, 12);

		break;
	case carType::Type::Black_viper:

		pathToTexture += "Black_viper/tire.png";
		nameTexture = "black_viperTire";

		for (auto i = 0;i < 4;++i)
			tires[i].setOrigin(5, 12);

		break;
	case carType::Type::Car:

		pathToTexture += "Car/tire.png";
		nameTexture = "carTire";

		for (auto i = 0;i < 4;++i)
			tires[i].setOrigin(5, 12);

		break;
	case carType::Type::Mini_truck:

		pathToTexture += "Mini_truck/tire.png";
		nameTexture = "mini_truckTire";

		for (auto i = 0;i < 4;++i)
			tires[i].setOrigin(5, 12);

		break;
	case carType::Type::Mini_van:
		break;
	case carType::Type::Police:

		pathToTexture += "Police/tire.png";
		nameTexture = "policeTire";

		for (auto i = 0;i < 4;++i)
			tires[i].setOrigin(5, 12);

		break;
	case carType::Type::Taxi:
		
		pathToTexture += "Taxi/tire.png";
		nameTexture = "taxiTire";

		for (auto i = 0;i < 4;++i)
			tires[i].setOrigin(5, 12);
		
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

void Tire::setPosition(const sf::Sprite* car, const carType::Type & type)
{
	switch (type)
	{
	case carType::Type::Ambulance:
		break;
	case carType::Type::Audi:

		tiresPos[0].setOrigin(car->getOrigin().x, car->getOrigin().y - 45);
		tiresPos[1].setOrigin(car->getOrigin().x - 89.f, car->getOrigin().y - 45);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x - 4.f, car->getOrigin().y - 170);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x + 2.f, car->getOrigin().y - 170);

		break;
	case carType::Type::Black_viper:

		tiresPos[0].setOrigin(car->getOrigin().x + 1.f, car->getOrigin().y - 50);
		tiresPos[1].setOrigin(car->getOrigin().x - 81.f, car->getOrigin().y - 50);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x - 2.f, car->getOrigin().y - 160);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x + 1.f, car->getOrigin().y - 160);

		break;
	case carType::Type::Car:

		tiresPos[0].setOrigin(car->getOrigin().x + 1, car->getOrigin().y - 40);
		tiresPos[1].setOrigin(car->getOrigin().x - 80.f, car->getOrigin().y - 40);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x, car->getOrigin().y - 165);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x, car->getOrigin().y - 165);

		break;
	case carType::Type::Mini_truck:

		tiresPos[0].setOrigin(car->getOrigin().x - 10, car->getOrigin().y - 60);
		tiresPos[1].setOrigin(car->getOrigin().x - 95.f, car->getOrigin().y - 60);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x, car->getOrigin().y - 180);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x, car->getOrigin().y - 180);

		break;
	case carType::Type::Mini_van:
		break;
	case carType::Type::Police:

		tiresPos[0].setOrigin(car->getOrigin().x + 1, car->getOrigin().y - 45);
		tiresPos[1].setOrigin(car->getOrigin().x - 86.f, car->getOrigin().y - 45);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x - 3, car->getOrigin().y - 170);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x + 1, car->getOrigin().y - 170);

		break;
	case carType::Type::Taxi:

		tiresPos[0].setOrigin(car->getOrigin().x, car->getOrigin().y - 30);
		tiresPos[1].setOrigin(car->getOrigin().x - 75.f, car->getOrigin().y - 30);

		tiresPos[2].setOrigin(tiresPos[0].getOrigin().x, car->getOrigin().y - 140);
		tiresPos[3].setOrigin(tiresPos[1].getOrigin().x, car->getOrigin().y - 140);

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

void Tire::rotate(const double & angle)
{
	for (int i = 0;i < 4;++i)
	{
		tires[i].rotate(static_cast<float>(angle));
		tiresPos[i].rotate(static_cast<float>(angle));

		tires[i].setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
	}
}

void Tire::setTraces()
{
	traces->setTraces();
}

void Tire::draw()
{
	for (auto i = 0;i < 4;++i)
		renderSprites::Instance().addToRender(tires + i);
}
