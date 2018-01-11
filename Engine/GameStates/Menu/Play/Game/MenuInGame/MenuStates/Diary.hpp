#pragma once

#include <SFML/Graphics.hpp>

#include "../menuStates.hpp"
#include "../../../../../../../Manager/Button.hpp"
#include "../../../../../../../Manager/Keyboard.hpp"

class Diary : public menuStates
{
public:

	Diary();
	~Diary();

	void setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	void drawActive() override;
	void drawUnactive() override;

private:
};