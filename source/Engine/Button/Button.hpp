#pragma once

#include <SFML/Graphics.hpp>

#include "../Rendering/Painter.hpp"
#include "../Text/Text.hpp"

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
	void Hover();
	void setDisabled();
	void draw();

	bool mouseOnClick();
	bool cursorIsOnButton();

	const Enabled &getEnabled();
	const sf::RectangleShape *getButtonSprite();

private:

	bool mouseIsPressedOnButton;

	Enabled *enabled;
	State *state;
	sf::RectangleShape *button;
	sf::RectangleShape *enabledSign;
	Text *text;
};