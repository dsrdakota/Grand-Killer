#include "Traces.hpp"
#include "../../../../Manager/Texture.hpp"
#include "../../../../Manager/renderSprites.hpp"
#include "../../../Car/Car.hpp"

Traces::Traces(Car *car, const sf::CircleShape *tiresPos)
{
	this->car = car;
	this->tiresPos = tiresPos;

	std::string carTypes[]{
		"Ambulance",
		"Audi",
		"Black_viper",
		"Car",
		"Mini_truck",
		"Police",
		"Taxi"
	};

	std::string carTypeString = carTypes[static_cast<int>(*car->getType())];

	textureManager::load("traceGrassTexture" + carTypeString, "data/Models/Cars/" + carTypeString + "/tracesTexture/grass.png");
	textureManager::load("traceAsphaltTexture" + carTypeString, "data/Models/Cars/" + carTypeString + "/tracesTexture/asphalt.png");
}

void Traces::setTraces()
{
	auto &traces = Map::Instance().getAllCarTraces();

	std::string carTypes[]{
		"Ambulance",
		"Audi",
		"Black_viper",
		"Car",
		"Mini_truck",
		"Police",
		"Taxi"
	};

	for (auto i = 0;i < 4;++i)
	{
		bool needAdd = false;
		std::string textureName = "";

		if (Map::isPointOnGrass(getCenterOfHitbox(tiresPos[i])) &&
			!isSameTraceOnVector(getCenterOfHitbox(tiresPos[i]), car->getSprite()->getRotation()))
		{
			needAdd = true;
			textureName = "traceGrassTexture" + carTypes[static_cast<int>(*car->getType())];
		}
		else if (fabs(*car->getOverSteerValue()) > 20 &&
			!isSameTraceOnVector(getCenterOfHitbox(tiresPos[i]), car->getSprite()->getRotation()))
		{
			needAdd = true;
			textureName = "traceAsphaltTexture" + carTypes[static_cast<int>(*car->getType())];
		}

		if (needAdd && textureName != "")
		{
			sf::Sprite *trace = new sf::Sprite(*textureManager::get(textureName));
			trace->setOrigin(trace->getGlobalBounds().width / 2.f, trace->getGlobalBounds().height / 2.f);
			trace->setPosition(getCenterOfHitbox(tiresPos[i]));
			trace->setRotation(tiresPos[i].getRotation());

			traces.push_back(std::make_pair(trace, 5));
		}
	}
	updateTimeInTrace();
}

void Traces::updateTimeInTrace()
{
	auto &traces = Map::Instance().getAllCarTraces();

	if (clock.time->asSeconds() > 1)
	{
		for (auto &i : traces)
			i.second--;

		clock.clock->restart();
		*clock.time = clock.time->Zero;
	}
}

bool Traces::isSameTraceOnVector(const sf::Vector2f &pos, const float &rot)
{
	auto &traces = Map::Instance().getAllCarTraces();

	for (const auto &i : traces)
	{
		if (i.first->getGlobalBounds().contains(pos) &&
			i.first->getRotation() == rot)
			return true;
	}
	return false;
}

sf::Vector2f Traces::getCenterOfHitbox(const sf::CircleShape &hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}