#include "Traces.hpp"
#include "../../../../Manager/Texture.hpp"
#include "../../../../Manager/renderSprites.hpp"
#include "../../../Car/Car.hpp"

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
		bool needAdd = false;
		std::string textureName = "";

		if (Map::isPointOnGrass(getCenterOfHitbox(tiresPos[i])) && 
			!isSameTraceOnVector(traces, getCenterOfHitbox(tiresPos[i]))) 
		{
			needAdd = true;
			textureName = "traceGrassTexture";
		}
		else if (fabs(*car->getOverSteerValue()) > 20 &&
			!isSameTraceOnVector(traces, getCenterOfHitbox(tiresPos[i])))
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

void Traces::draw()
{
	if (traces.size() > 600)
	{
		for (auto i = 0;i < 10;++i)
			delete traces[i].first;

		traces.erase(traces.begin(), traces.begin() + 10);
	}

	for (size_t i = 0;i<traces.size();i++)
	{
		if (traces[i].second <= 0 &&
			Map::isOutsideView(sf::Vector2f(traces[i].first->getGlobalBounds().left + traces[i].first->getGlobalBounds().width,
				traces[i].first->getGlobalBounds().top + traces[i].first->getGlobalBounds().height)))
		{
			delete traces[i].first;
			traces.erase(traces.begin() + i, traces.begin() + i + 1);
			--i;
		}
		else if (!Map::isOutsideView(sf::Vector2f(traces[i].first->getGlobalBounds().left + traces[i].first->getGlobalBounds().width,
			traces[i].first->getGlobalBounds().top + traces[i].first->getGlobalBounds().height)))

			renderSprites::Instance().addToRender(traces[i].first);
	}
}

void Traces::updateTimeInTrace()
{
	if (clock.time->asSeconds() > 1)
	{
		for (auto &i : traces)
			i.second--;

		clock.clock->restart();
		*clock.time = clock.time->Zero;
	}
}

bool Traces::isSameTraceOnVector(std::vector<std::pair<sf::Sprite*, int>> &tracesVector, const sf::Vector2f &pos)
{
	for (const auto &i : tracesVector)
		if (i.first->getGlobalBounds().contains(pos))
			return true;
	return false;
}

sf::Vector2f Traces::getCenterOfHitbox(const sf::CircleShape &hitbox)
{
	return sf::Vector2f(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2,
		hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2);
}
