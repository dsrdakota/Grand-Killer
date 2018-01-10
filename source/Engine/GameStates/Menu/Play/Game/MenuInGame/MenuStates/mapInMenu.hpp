#pragma once

#include <SFML/Graphics.hpp>

#include "../menuStates.hpp"
#include "../../../../../../../Manager/Button.hpp"

class mapInMenu : public menuStates
{
public:

	mapInMenu();
	~mapInMenu();

	void setPosition(const sf::Vector2f &menuPos) override;
	void draw() override;

private:
};