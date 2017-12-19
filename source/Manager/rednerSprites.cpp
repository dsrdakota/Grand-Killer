#include "renderSprites.hpp"

void renderSprites::addToRender(sf::Drawable *object)
{
	sprites.push_back(object);
}

void renderSprites::run()
{
	window->clear();

	for (const auto &i : sprites)
		window->draw(*i);

	window->display();

	clearVector();
}
