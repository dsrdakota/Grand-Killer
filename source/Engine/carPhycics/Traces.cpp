#include "Traces.hpp"
#include "../../Manager/Texture.hpp"
#include "../../Engine/GameStates/Menu/Play/Game/Map.hpp"
#include "../../Manager/renderSprites.hpp"
#include "../Car/Car.hpp"

#include <iostream>

Traces::Traces(Car *car, const sf::CircleShape *tiresPos, const std::vector<sf::CircleShape*>*tiresHitbox)
{
	this->car = car;
	this->tiresPos = tiresPos;
	this->tiresHitbox = tiresHitbox;
	traceGrassTexture = new sf::Texture(*textureManager::load("traceGrassTexture","data/Models/Cars/Taxi/tracesTexture/grass.png"));
	traceAsphaltTexture = new sf::Texture(*textureManager::load("traceAsphaltTexture", "data/Models/Cars/Taxi/tracesTexture/asphalt.png"));
}

Traces::~Traces()
{
	delete traceGrassTexture;
	delete traceAsphaltTexture;
}

void Traces::setTraces()
{
	sf::Image *grassHitbox = Map::Instance().getGrassHitbox();
	int x=0, y=0; // rect Texture
	for (auto i = 0;i < 4;++i)
	{
		if (grassHitbox->getPixel(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
			tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2) == sf::Color(133, 91, 0) && // hitbox is on Grass
			!isSameTraceOnVector(sf::Vector2f(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2, // trace isnt in vector
				tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2),
				tiresPos[i].getRotation()))
		{
			sf::Sprite *trace = new sf::Sprite(*traceGrassTexture);
			trace->setOrigin(2.5, 2.5);
			trace->setPosition(tiresPos[i].getGlobalBounds().left + tiresPos[i].getGlobalBounds().width / 2,
				tiresPos[i].getGlobalBounds().top + tiresPos[i].getGlobalBounds().height / 2);
			trace->setRotation(tiresPos[i].getRotation());

			traces.push_back(std::make_pair(trace, 5));

			continue;
		}


		for (auto j = 0;j < 6;j++)
		{
			if (grassHitbox->getPixel(tiresHitbox[i][j]->getGlobalBounds().left + tiresHitbox[i][j]->getGlobalBounds().width / 2,
				tiresHitbox[i][j]->getGlobalBounds().top + tiresHitbox[i][j]->getGlobalBounds().height / 2) == sf::Color(133, 91, 0) && // hitbox is on Grass
				!isSameTraceOnVector(sf::Vector2f(tiresHitbox[i][j]->getGlobalBounds().left + tiresHitbox[i][j]->getGlobalBounds().width / 2, // trace isnt in vector
					tiresHitbox[i][j]->getGlobalBounds().top + tiresHitbox[i][j]->getGlobalBounds().height / 2),
					tiresHitbox[i][j]->getRotation()))
			{
				sf::Sprite *trace = new sf::Sprite(*traceGrassTexture);
				trace->setTextureRect(sf::IntRect(x, y, 4, 9));
				trace->setOrigin(2.5, 2.5);
				trace->setPosition(tiresHitbox[i][j]->getGlobalBounds().left + tiresHitbox[i][j]->getGlobalBounds().width / 2,
					tiresHitbox[i][j]->getGlobalBounds().top + tiresHitbox[i][j]->getGlobalBounds().height / 2);
				trace->setRotation(tiresHitbox[i][j]->getRotation());

				traces.push_back(std::make_pair(trace, 5));

				if (j % 2 == 0)
					x = 0;
				else
					x = 4;

				if (j % 2 == 0 && j != 0)
					y += 9;

			}
		}
	}
	updateTimeInTrace();
}

void Traces::draw()
{
	if (traces.size() > 4000)
	{
		for (auto i = 0;i < 50;++i)
			delete traces[i].first;
		traces.erase(traces.begin(), traces.begin() + 50);
	}
	for (auto i=0;i<traces.size();i++)
	{
		if (traces[i].second <= 0 && Map::isOutsideView(traces[i].first->getPosition()))
		{
			delete traces[i].first;
			traces.erase(traces.begin() + i, traces.begin() + i + 1);
		}
		else if(!Map::isOutsideView(traces[i].first->getPosition()))
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

bool Traces::isSameTraceOnVector(const sf::Vector2f & pos, const float & rot)
{
	for (const auto &i : traces)
		if (i.first->getPosition() == pos && i.first->getRotation() == rot)
			return true;
	return false;
}
