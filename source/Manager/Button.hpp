#pragma once

#include <SFML/Graphics.hpp>

#include "Text.hpp"
#include "../Game.hpp"

class Button
{
public:

	enum class State
	{
		normalButton,
		header
	};

	enum class Enabled
	{
		False,
		True
	};

	Button(const sf::Vector2f &size, const unsigned &sizeTag, const std::string &tag, const State &state = State::normalButton);
	~Button();

	void setPosition(const sf::Vector2f &pos);
	void setEnabled();
	bool isHover();
	void setDisabled();
	void draw();

	bool mouseOnClick();
	bool cursorIsOnButton();

	const Enabled &getEnabled();
	const sf::RectangleShape *getButtonSprite();

private:

	sf::RenderWindow *window;
	Enabled *enabled;
	State *state;
	sf::RectangleShape *button;
	sf::RectangleShape *enabledSign;
	Text *text;
};