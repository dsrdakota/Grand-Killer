#pragma once

#include <SFML/Graphics.hpp>

#include "../../Player/playerStates.hpp"

class playerMechanics : public playerStates
{
public:
	void toControl() override;
	void setCamera() override;
	void draw() override;
};