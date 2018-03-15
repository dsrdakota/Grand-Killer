#pragma once

#include "../Objects/Light.hpp"

#include "../../Engine/Engine.hpp"

class TrafficLights
{
public:

	TrafficLights();
	~TrafficLights();

	std::vector<sf::CircleShape*> getAllLightsHitbox();

	void drawUnder();
	void drawOn();

private:

	enum class State
	{
		Down,
		Right,
		Up,
		Left
	};

	std::vector<Light*>lightsUp;
	std::vector<Light*>lightsDown;
	std::vector<Light*>lightsLeft;
	std::vector<Light*>lightsRight;

	State *lightState;
	Time clock;
	int timeOfAnimation;

	void playAnimation();
	void checkLight(const std::vector<Light*> &lights);
	void changeLight(const std::vector<Light*> &lights, const std::string &lightName);
	void deleteLights(const std::vector<Light*> &lights);
	void draw(const std::vector<Light*> &lights,const int &drawState);
};