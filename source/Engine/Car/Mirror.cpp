#include "Mirror.hpp"

#include "../../Manager/Texture.hpp"
#include "../../Manager/renderSprites.hpp"
#include "../GameStates/Menu/Play/Game/Map.hpp"

Mirror::Mirror(const carType::Type & type)
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

		setDefaultVars();

		mirrors[0].setTexture(*textureManager::load("mirrorTaxiLeft", "data/Models/Cars/Taxi/mirrors/left.png"));
		mirrors[1].setTexture(*textureManager::load("mirrorTaxiRight", "data/Models/Cars/Taxi/mirrors/right.png"));

		break;
	case carType::Type::Truck:
		break;
	}
}

Mirror::~Mirror()
{
	delete[]mirrors;
	delete[]hitboxes;
	delete[]timeOfDrawUnable;
	delete[]clock;
}

sf::Sprite * Mirror::getMirrors()
{
	return mirrors;
}

void Mirror::setPosition(const sf::ConvexShape * car, const carType::Type & type)
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

		mirrors[0].setOrigin(car->getOrigin().x + 10, car->getOrigin().y -52);
		hitboxes[0].setOrigin(mirrors[0].getOrigin().x , mirrors[0].getOrigin().y - 5);

		mirrors[1].setOrigin(car->getOrigin().x - 78, car->getOrigin().y - 52);
		hitboxes[1].setOrigin(mirrors[1].getOrigin().x - 5, mirrors[1].getOrigin().y - 5);

		break;
	case carType::Type::Truck:
		break;
	}

	for (auto i = 0;i < 2;++i)
	{
		mirrors[i].setPosition(car->getPosition());
		mirrors[i].setRotation(car->getRotation());

		hitboxes[i].setPosition(car->getPosition());
		hitboxes[i].setRotation(car->getRotation());
	}
}

void Mirror::move(const sf::Vector2f & offset)
{
	for (int i = 0;i < 2;++i)
		if (!isBroken[i])
		{
			mirrors[i].move(offset);
			hitboxes[i].move(offset);
		}
}

void Mirror::rotate(const double & angle)
{
	for (int i = 0;i < 2;++i)
		if (!isBroken[i])
		{
			mirrors[i].rotate(static_cast<float>(angle));
			hitboxes[i].rotate(static_cast<float>(angle));
		}
}

void Mirror::checkCollision()
{
	for (auto i = 0;i < 2;++i)
	{
		if (!isBroken[i])
		{
			if (isCollision(i))
				playAnimation(i);
		}
		else if (isDrawAble[i])
			playAnimation(i);
	}
}

void Mirror::drawUnder()
{
	for (auto i = 0;i < 2;++i)
		if (isDrawAble[i] && isBroken[i])
			renderSprites::Instance().addToRender(&mirrors[i]);
}

void Mirror::drawOn()
{
	for (auto i = 0;i < 2;++i)
		if (isDrawAble[i] && !isBroken[i])
			renderSprites::Instance().addToRender(&mirrors[i]);
}

void Mirror::setDefaultVars()
{
	mirrors = new sf::Sprite[2];
	hitboxes = new sf::CircleShape[2];
	timeOfDrawUnable = new int[2];
	clock = new Time[2];

	hitboxes[0].setRadius(2);
	hitboxes[1].setRadius(2);

	for (auto i = 0;i < 2;++i)
	{
		isBroken[i] = false;
		isDrawAble[i] = true;
		timeOfDrawUnable[i] = 10;
	}
}

bool Mirror::isCollision(const size_t &index)
{
	auto collisionHitbox = Map::Instance().getCollisionHitbox();
	auto allSignsHitbox = Map::Instance().getAllTrafficSigns()->getAllSignsHitbox();
	auto allLightsHitbox = Map::Instance().getAllTrafficLights()->getAllLightsHitbox();

	if (collisionHitbox->getPixel(static_cast<unsigned>(hitboxes[index].getGlobalBounds().left + hitboxes[index].getGlobalBounds().width / 2),
		static_cast<unsigned>(hitboxes[index].getGlobalBounds().top + hitboxes[index].getGlobalBounds().height / 2)) == sf::Color(255, 0, 0))
		return true;

	for (const auto &i : allLightsHitbox)
		if (i->getGlobalBounds().intersects(hitboxes[index].getGlobalBounds()))
			return true;

	for (const auto &i : allSignsHitbox)
		if (i->getGlobalBounds().intersects(hitboxes[index].getGlobalBounds()))
			return true;

	return false;
}

void Mirror::playAnimation(const size_t & index)
{
	isBroken[index] = true;

	if (clock[index].time->asSeconds() >= 1)
	{
		timeOfDrawUnable[index]--;
		clock[index].clock->restart();
		*clock[index].time = sf::Time::Zero;
	}

	if (timeOfDrawUnable[index] <= 0 && 
		Map::isOutsideView(sf::Vector2f(hitboxes[index].getGlobalBounds().left + hitboxes[index].getGlobalBounds().width/2,
			hitboxes[index].getGlobalBounds().top + hitboxes[index].getGlobalBounds().height/2)))
		isDrawAble[index] = false;
}