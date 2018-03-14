#include "View.hpp"

View::View()
{
	view = new sf::View();
}

View::~View()
{
	delete view;
}

sf::Vector2u View::getSize()
{
	return Instance().size;
}

bool View::isOutSideView(const sf::Vector2f & position)
{
	return Instance().getViewBox().contains(position);
}

bool View::isOutSideView(const sf::FloatRect & box)
{
	return Instance().getViewBox().intersects(box);
}

sf::FloatRect View::getViewBox()
{
	const sf::Vector2f viewSize = view->getSize();
	const sf::Vector2f viewPos = view->getCenter();

	return sf::FloatRect(viewPos, viewSize);
}

sf::Vector2f View::getUpLeftCornerPosOfCurrentView()
{
	auto &view = Instance();
	return sf::Vector2f(view.view->getCenter().x - view.view->getSize().x / 2,
		view.view->getCenter().y - view.view->getSize().y / 2);
}