#pragma once

#include "../IObject.hpp"

class Player : public IObject
{
public:

	Player();

private:

	void controlBody() override;
	void controlCar() override;

};