#pragma once

#include "Sign.hpp"

class TrafficSigns
{
public:

	TrafficSigns();
	~TrafficSigns();

	void drawUnder();
	void drawOn();

private:

	Sign *signs;
};