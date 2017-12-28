#include "TrafficLights.hpp"

#include "../../../../../../Manager/texture.hpp"
#include "../../../../../../Manager/renderSprites.hpp"

TrafficLights::TrafficLights()
{
	textureManager::load("stake", "data/Map/Traffic/Lights/stake.png");

	for(auto i=1;i<=4;++i)
		textureManager::load("light" + std::to_string(i), "data/Map/Traffic/Lights/light" + std::to_string(i) + ".png");

	for (auto i = 0;i < 2;++i)
	{
		Light *example = new Light;
		lightsDown.push_back(example);
	}

	for (auto i = 0;i < 1;++i)
	{
		Light *example = new Light;
		lightsUp.push_back(example);
	}

	for (auto i = 0;i < 2;++i)
	{
		Light *example = new Light;
		lightsLeft.push_back(example);
	}

	for (auto i = 0;i < 2;++i)
	{
		Light *example = new Light;
		lightsRight.push_back(example);
	}

	// yeah i know...

	lightsDown[0]->setPosition(sf::Vector2f(1762, 2269));
	lightsDown[1]->setPosition(sf::Vector2f(1763, 3902));

	lightsUp[0]->setPosition(sf::Vector2f(1412, 3513), 180);

	lightsLeft[0]->setPosition(sf::Vector2f(1765,1948), -90);
	lightsLeft[1]->setPosition(sf::Vector2f(1765, 3515), -90);

	lightsRight[0]->setPosition(sf::Vector2f(1415,3885), 90);
	lightsRight[1]->setPosition(sf::Vector2f(1409, 2264), 90);

	lightState = new State(State::Down);
}

TrafficLights::~TrafficLights()
{
	delete lightState;
}

void TrafficLights::drawUnder()
{
	draw(lightsDown);
	draw(lightsUp);
	draw(lightsLeft);
	draw(lightsRight);
}

void TrafficLights::drawOn()
{
	draw(lightsDown);
	draw(lightsUp);
	draw(lightsLeft);
	draw(lightsRight);
}

void TrafficLights::draw(const std::vector<Light*>& lights)
{
	for (size_t i = 0;i<lights.size();++i)
	{
		renderSprites::Instance().addToRender(lights[i]->getStakeSprite());
		renderSprites::Instance().addToRender(lights[i]->getLightSprite());
		renderSprites::Instance().addToRender(lights[i]->getLightHitbox());
	}
}
