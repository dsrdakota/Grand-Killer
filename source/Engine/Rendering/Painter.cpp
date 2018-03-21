#include "Painter.hpp"

void Painter::addToDraw(sf::Drawable *object)
{
	objects.push_back(object);
}

void Painter::addToInterfaceDraw(sf::Drawable * object)
{
	interface.push_back(object);
}

void Painter::run()
{
	window->clear();

	for (const auto &i : objects)
		window->draw(*i);

	sf::View view = window->getView();

	window->setView(window->getDefaultView());

	for (const auto &i : interface)
		window->draw(*i);

	window->setView(view);

	window->display();

	objects.clear();
	interface.clear();
}