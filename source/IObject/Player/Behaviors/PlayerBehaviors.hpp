#pragma once

#include "../../Behaviors/ObjectBehaviors.hpp"

#include "../../../Engine/Engine.hpp"

class PlayerBehaviors : public ObjectBehaviors
{
public:

	PlayerBehaviors();
	~PlayerBehaviors();

private:

	Time * timeShowingName;
	Text *carName;

	void controlBody() override;
	void controlCar() override;
	void showCarName() override;
	void updateCarName();
};