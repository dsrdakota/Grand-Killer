#include "playerMechanics.hpp"

void playerMechanics::toControl()
{
}

float playerMechanics::getRotation()
{
	return 0;
}

void playerMechanics::setCamera()
{
	view->setView(sf::Vector2f(0, 0));
}


void playerMechanics::draw()
{
	Text example(sf::Color::Blue, 50, "Player");

	window->clear();

	window->draw(*example.text);

	window->display();
}