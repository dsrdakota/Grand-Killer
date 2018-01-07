#include "Traces.hpp"
#include "../../../../Manager/Texture.hpp"
#include "../../../../Manager/renderSprites.hpp"
#include "../../../GamePhysics/Map/Map.hpp"
#include "../../../Car/Car.hpp"

// need to optimise it but LATER

Traces::Traces(Car *car, const sf::CircleShape *tiresPos)
{
	this->car = car;
	this->tiresPos = tiresPos;
	textureManager::load("traceGrassTexture","data/Models/Cars/Taxi/tracesTexture/grass.png");
	textureManager::load("traceAsphaltTexture", "data/Models/Cars/Taxi/tracesTexture/asphalt.png");
}

void Traces::setTraces()
{
	for (auto i = 0;i < 4;++i)
	{
		if (Map::isPointOnGrass(getCenterOfHitbox(tiresPos[i])) && // hitbox is on Grass
			!isSameTraceOnVector(tracesGrassPos, sf::Vector2f(getCenterOfHitbox(tiresPos[i])))) // trace isnt in vector

			tracesGrassPos.push_back(std::make_pair(std::make_pair(getCenterOfHitbox(tiresPos[i]), tiresPos[i].getRotation()), 5));

		else if (fabs(*car->getOverSteerValue()) > 20 && 
			!isSameTraceOnVector(tracesAsphaltPos, getCenterOfHitbox(tiresPos[i])) &&
			!isSameTraceOnVector(tracesGrassPos, getCenterOfHitbox(tiresPos[i])))

			tracesAsphaltPos.push_back(std::make_pair(std::make_pair(getCenterOfHitbox(tiresPos[i]), tiresPos[i].getRotation()),5));
	}
	updateTimeInTrace();
}

void Traces::draw()
{
	drawOneTypeTraces(tracesGrassPos, "traceGrassTexture");
	drawOneTypeTraces(tracesAsphaltPos, "traceAsphaltTexture");
}

void Traces::drawOneTypeTraces(std::vector<std::pair<std::pair<sf::Vector2f, float>, int>> &tracesPos, const std::string &nameTexture)
{
	if (tracesPos.size() > 400)
		tracesPos.erase(tracesPos.begin(), tracesPos.begin() + 10);

	for (size_t i = 0;i<tracesPos.size();i++)
	{
		if (tracesPos[i].second <= 0 && Map::isOutsideView(tracesPos[i].first.first))
		{
			tracesPos.erase(tracesPos.begin() + i, tracesPos.begin() + i + 1);
			--i;
		}
		else if (!Map::isOutsideView(tracesPos[i].first.first))
		{
			sf::Sprite *trace = new sf::Sprite(*textureManager::get(nameTexture));
			trace->setOrigin(2.5, 2.5);
			trace->setPosition(tracesPos[i].first.first);
			trace->setRotation(tracesPos[i].first.second);
			renderSprites::Instance().addToRender(trace);
		}
	}
}

void Traces::updateTimeInTrace()
{
	if (clock.time->asSeconds() > 1)
	{
		for (auto &i : tracesAsphaltPos)
			i.second--;

		for (auto &i : tracesGrassPos)
			i.second--;

		clock.clock->restart();
		*clock.time = clock.time->Zero;
	}
}

bool Traces::isSameTraceOnVector(std::vector<std::pair<std::pair<sf::Vector2f, float>, int>>tracesPosVector, const sf::Vector2f &pos)
{
	sf::Sprite *trace = new sf::Sprite(*textureManager::get("traceGrassTexture"));
	for (const auto &i : tracesPosVector)
	{
		trace->setOrigin(2.5, 2.5);
		trace->setPosition(i.first.first);
		trace->setRotation(i.first.second);
		if (trace->getGlobalBounds().contains(pos))
			return true;
	}
	return false;
}

sf::Vector2f Traces::getCenterOfHitbox(const sf::CircleShape &hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}
