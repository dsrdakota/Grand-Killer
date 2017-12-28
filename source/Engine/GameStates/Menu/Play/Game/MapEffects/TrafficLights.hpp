#pragma once
#include "Light.hpp"
#include <vector>
class TrafficLights
{
public:

	TrafficLights();
	~TrafficLights();

	void drawUnder();
	void drawOn();

private:

	enum class State
	{
		Up,
		Down,
		Left,
		Right
	};

	std::vector<Light*>lightsUp;
	std::vector<Light*>lightsDown;
	std::vector<Light*>lightsLeft;
	std::vector<Light*>lightsRight;

	State *lightState;

	void draw(const std::vector<Light*> &lights);
};