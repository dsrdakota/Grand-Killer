#pragma once

#include <SFML/Graphics.hpp>

#include "../../States.hpp"
#include "../../../../../../Engine/Engine.hpp"

class Statistics : public MenuStates
{
public:

	Statistics();
	~Statistics();

	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	bool isActive() override;
	void drawActive() override;
	void drawUnactive() override;

private:

	enum class optionState
	{
		Skills,
		General,
		Crimes,
		Vehicles,
		Cash,
		Combat,
		Weapons,
	};

	optionState *state;

	std::vector<Button*>buttons;
	std::vector<std::pair<Text*, sf::Sprite*>>navigation;
	sf::RectangleShape *hitboxClick;
	sf::RectangleShape *backgroundRight;

	Time timeChangeStates;
	int cooldownChangeStates;

	Text* centerTextOfOption;

	bool active;
	bool isMousePressed;

	void toControl();

	bool isMouseClickOnHitbox();
	void resertCooldown();
};