#include "Button.hpp"

#include "renderSprites.hpp"

Button::Button(const sf::Vector2f & size, const unsigned &sizeTag, const std::string & tag, const State & state)
	: window(Game::Instance().getWindow())
{
	this->state = new State(state);
	enabled = new Enabled(Enabled::False);
	button = new sf::RectangleShape(size);
	button->setFillColor(sf::Color(0, 0, 0, 150));
	text = new Text(sf::Color::White, sizeTag, tag);

	enabledSign = new sf::RectangleShape(sf::Vector2f(size.x,4.f));
	enabledSign->setFillColor(sf::Color(71, 233, 83));

	mouseIsPressedOnButton = false;
}

Button::~Button()
{
	delete button;
	delete text;
	delete state;
	delete enabled;
}

void Button::setPosition(const sf::Vector2f & pos)
{
	button->setPosition(pos);
	
	if (*state == State::normalButton)
		text->text->setPosition(pos.x + 10, pos.y + button->getGlobalBounds().height / 2 - text->text->getGlobalBounds().height / 2 - 3);
	else if (*state == State::header)
	{
		text->text->setPosition(pos.x + button->getGlobalBounds().width / 2 - text->text->getGlobalBounds().width / 2, pos.y + button->getGlobalBounds().height / 2 - 10);
		enabledSign->setPosition(pos.x, pos.y - 3.f);
	}
}

void Button::setEnabled()
{
	*enabled = Enabled::True;
	button->setFillColor(sf::Color::White);
	text->text->setFillColor(sf::Color(0,0,0));
}

void Button::Hover()
{
	if (*enabled == Enabled::False)
	{
		if (cursorIsOnButton())
			button->setFillColor(sf::Color(128, 128, 128, 180));
		else
			button->setFillColor(sf::Color(0, 0, 0, 150));
	}
}

void Button::setDisabled()
{
	*enabled = Enabled::False;
	button->setFillColor(sf::Color(0, 0, 0, 150));
	text->text->setFillColor(sf::Color::White);
}

bool Button::mouseOnClick()
{
	if (cursorIsOnButton() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mouseIsPressedOnButton = true;

	if (mouseIsPressedOnButton && cursorIsOnButton() && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mouseIsPressedOnButton = false;
		return true;
	}

	if (!cursorIsOnButton())
		mouseIsPressedOnButton = false;

	return false;
}

bool Button::cursorIsOnButton()
{
	if (button->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
		return true;
	return false;
}

const Button::Enabled &Button::getEnabled()
{
	return *enabled;
}

const sf::RectangleShape * Button::getButtonSprite()
{
	return button;
}

void Button::draw()
{
	renderSprites::Instance().addToRender(button);
	renderSprites::Instance().addToRender(text->text);
	if (*enabled == Enabled::True && *state == State::header)
		renderSprites::Instance().addToRender(enabledSign);
}