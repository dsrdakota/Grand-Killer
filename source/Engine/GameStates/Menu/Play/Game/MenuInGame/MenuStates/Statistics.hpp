#pragma once

#include <SFML/Graphics.hpp>

#include "../menuStates.hpp"
#include "../../../../../../../Manager/Button.hpp"
#include "../../../../../../../Manager/Keyboard.hpp"

class Statistics : public menuStates
{
public:

	Statistics();
	~Statistics();

	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	void drawActive() override;
	void drawUnactive() override;

private:
};