#pragma once

#include "../IObject.hpp"

class Player : public IObject
{
public:

	Player(const sf::Vector2f &startPos, const float &startRot);

private:

	void controlBody() override;
	void controlCar() override;

};