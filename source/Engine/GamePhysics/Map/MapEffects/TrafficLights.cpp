#include "TrafficLights.hpp"

#include "../../../../Manager/texture.hpp"
#include "../../../../Manager/renderSprites.hpp"
#include "../Map.hpp"

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

	timeOfAnimation = 6;
}

TrafficLights::~TrafficLights()
{
	deleteLights(lightsDown);
	deleteLights(lightsLeft);
	deleteLights(lightsRight);
	deleteLights(lightsUp);

	delete lightState;
}

std::vector<sf::CircleShape*> TrafficLights::getAllLightsHitbox()
{
	std::vector<sf::CircleShape*>hitboxes;
	
	for (const auto &i : lightsDown)
		hitboxes.push_back(i->getLightHitbox());

	for (const auto &i : lightsUp)
		hitboxes.push_back(i->getLightHitbox());

	for (const auto &i : lightsLeft)
		hitboxes.push_back(i->getLightHitbox());
	
	for (const auto &i : lightsRight)
		hitboxes.push_back(i->getLightHitbox());
	
	return hitboxes;
}

void TrafficLights::drawUnder()
{
	playAnimation();

	draw(lightsDown, -1);
	draw(lightsUp, -1);
	draw(lightsLeft, -1);
	draw(lightsRight, -1);
}

void TrafficLights::drawOn()
{
	draw(lightsDown, 1);
	draw(lightsUp, 1);
	draw(lightsLeft, 1);
	draw(lightsRight, 1);
}

void TrafficLights::playAnimation()
{
	switch (*lightState)
	{
	case State::Down:

		checkLight(lightsDown);

		break;
	case State::Left:

		checkLight(lightsLeft);

		break;
	case State::Right:

		checkLight(lightsRight);

		break;
	case State::Up:

		checkLight(lightsUp);

		break;
	}

	if (clock.time->asSeconds() >= 1)
	{
		timeOfAnimation--;
		clock.clock->restart();
		*clock.time = sf::Time::Zero;
	}

	 // next State
	if (timeOfAnimation <= 0)
	{
		*lightState =
			static_cast<int>(*lightState) < 3 ? static_cast<State>(static_cast<int>(*lightState) + 1) :
			State::Down;
		timeOfAnimation = 6;
	}
}

void TrafficLights::checkLight(const std::vector<Light*>& lights)
{
	for (const auto &i : lights)
		i->checkCollision();

	if (timeOfAnimation == 6)
		changeLight(lights, "light2");
	else if (timeOfAnimation < 6 && timeOfAnimation > 2)
		changeLight(lights, "light3");
	else if (timeOfAnimation == 2)
		changeLight(lights, "light4");
	else if (timeOfAnimation == 1)
		changeLight(lights, "light1");
}

void TrafficLights::changeLight(const std::vector<Light*>& lights, const std::string & lightName)
{
	for (const auto &i : lights)
		if (i->getDrawState() != -1) // is not broken
			i->getLightSprite()->setTexture(*textureManager::get(lightName));
}

void TrafficLights::deleteLights(const std::vector<Light*>& lights)
{
	for (const auto &i : lights)
		delete i;
}

void TrafficLights::draw(const std::vector<Light*>& lights, const int &drawState)
{
	for (size_t i = 0;i<lights.size();++i)
		if (lights[i]->getDrawState() == drawState)
		{
			if (!Map::isOutsideView(sf::Vector2f(lights[i]->getStakeSprite()->getGlobalBounds().left, lights[i]->getStakeSprite()->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(lights[i]->getStakeSprite()->getGlobalBounds().left + lights[i]->getStakeSprite()->getGlobalBounds().width, lights[i]->getStakeSprite()->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(lights[i]->getStakeSprite()->getGlobalBounds().left + lights[i]->getStakeSprite()->getGlobalBounds().width, lights[i]->getStakeSprite()->getGlobalBounds().top + lights[i]->getStakeSprite()->getGlobalBounds().height)) ||
				!Map::isOutsideView(sf::Vector2f(lights[i]->getStakeSprite()->getGlobalBounds().left, lights[i]->getStakeSprite()->getGlobalBounds().top + lights[i]->getStakeSprite()->getGlobalBounds().height)))
			{
				renderSprites::Instance().addToRender(lights[i]->getStakeSprite());
				renderSprites::Instance().addToRender(lights[i]->getLightSprite());
			}
		}
}
