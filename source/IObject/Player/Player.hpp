#pragma once

#include "../IObject.hpp"
#include "Behaviors/PlayerBehaviors.hpp"

#include "../../Engine/Engine.hpp"

class Player : public IObject
{
public:

	Player(const sf::Vector2f &startPos, const float &startRot);
	~Player();

	PlayerBehaviors* getBehaviors() override;

private:

	PlayerBehaviors * behaviors;
};