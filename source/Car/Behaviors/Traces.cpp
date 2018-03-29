#include "Traces.hpp"

#include "../../Engine/Engine.hpp"

#include "../Car.hpp"
#include "../Attributes/Hitbox.hpp"

Traces::Traces(Car *car, const sf::CircleShape *tiresPos)
{
	this->car = car;
	this->tiresPos = tiresPos;
}

void Traces::setTraces()
{
	auto &traces = Map::Instance().getAllCarTraces();

	for (size_t i = 0;i < car->getCountTires();++i)
	{
		bool needAdd = false;
		std::string textureName = "";

		if (Map::isPointOnGrass(Hitbox::getCenterOfHitbox(tiresPos[i])) &&
			!isSameTraceOnVector(Hitbox::getCenterOfHitbox(tiresPos[i]), car->getSprite()->getRotation()))
		{
			needAdd = true;
			textureName = car->getName() + "_grass";
		}
		else if (fabs(*car->getToTurnClass()->getSlidePhycics()->getOverSteer()) > 20 &&
			!isSameTraceOnVector(Hitbox::getCenterOfHitbox(tiresPos[i]), car->getSprite()->getRotation()))
		{
			needAdd = true;
			textureName = car->getName() + "_asphalt";
		}

		if (needAdd && textureName != "")
		{
			sf::Sprite *trace = new sf::Sprite(*TextureManager::get(textureName));
			trace->setOrigin(trace->getGlobalBounds().width / 2.f, trace->getGlobalBounds().height / 2.f);
			trace->setPosition(Hitbox::getCenterOfHitbox(tiresPos[i]));
			trace->setRotation(tiresPos[i].getRotation());

			traces.push_back(std::make_pair(trace, new int(8))); // time trace
		}
	}
}

bool Traces::isSameTraceOnVector(const sf::Vector2f &pos, const float &rot)
{
	auto &traces = Map::Instance().getAllCarTraces();

	for(const auto &i: traces)
		if (i.first->getGlobalBounds().contains(pos) && i.first->getRotation() == rot)
			return true;
	return false;
}