#include "Traces.hpp"
#include "../../../../Manager/Texture.hpp"
#include "../../../../Manager/renderSprites.hpp"
#include "../../../Car/Car.hpp"

Traces::Traces(Car *car, const sf::CircleShape *tiresPos)
{
	this->car = car;
	this->tiresPos = tiresPos;
	textureManager::load("traceGrassTexture", "data/Models/Cars/Taxi/tracesTexture/grass.png");
	textureManager::load("traceAsphaltTexture", "data/Models/Cars/Taxi/tracesTexture/asphalt.png");
}

void Traces::setTraces()
{
	auto &traces = Map::Instance().getAllCarTraces();

	for (auto i = 0;i < 4;++i)
	{
		bool needAdd = false;
		std::string textureName = "";

		if (Map::isPointOnGrass(getCenterOfHitbox(tiresPos[i])) &&
			!isSameTraceOnVector(getCenterOfHitbox(tiresPos[i]), car->getSprite()->getRotation()))
		{
			needAdd = true;
			textureName = "traceGrassTexture";
		}
		else if (fabs(*car->getOverSteerValue()) > 20 &&
			!isSameTraceOnVector(getCenterOfHitbox(tiresPos[i]), car->getSprite()->getRotation()))
		{
			needAdd = true;
			textureName = "traceAsphaltTexture";
		}

		if (needAdd && textureName != "")
		{
			sf::Sprite *trace = new sf::Sprite(*textureManager::get(textureName));
			trace->setOrigin(2.5, 2.5);
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