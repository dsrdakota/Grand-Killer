#include "Painter.hpp"

void Painter::addToDraw(sf::Drawable *object)
{
	objects.push_back(object);
}

void Painter::run()
{
	window->clear();

	for (const auto &i : objects)
		window->draw(*i);

	window->display();

	objects.clear();
}