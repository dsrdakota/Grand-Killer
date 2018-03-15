#include "View.hpp"

#include "../../Map/MapsManager.hpp"
#include "../GlobalSettings/GlobalSettings.hpp"

View::View()
{
	view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(static_cast<float>(GlobalSettings::getWidth()), static_cast<float>(GlobalSettings::getHeight())));
}

View::~View()
{
	delete view;
}

sf::View * View::getView()
{
	return Instance().view;
}

sf::Vector2u View::getSize()
{
	return static_cast<sf::Vector2u>(Instance().view->getSize());
}

void View::updateView(IObject *player)
{
	Instance().setView(player->getPosition());

	if (Instance().view->getCenter().x - Instance().view->getSize().x / 2 < 0)
		Instance().setView(sf::Vector2f(Instance().view->getSize().x / 2, Instance().view->getCenter().y));

	else if (Instance().view->getCenter().x + Instance().view->getSize().x / 2 > MapsManager::getMainmap()->getSize().x)
		Instance().setView(sf::Vector2f(MapsManager::getMainmap()->getSize().x - Instance().view->getSize().x / 2, Instance().view->getCenter().y));

	if (Instance().view->getCenter().y - Instance().view->getSize().y / 2 < 0)
		Instance().setView(sf::Vector2f(Instance().view->getCenter().x, Instance().view->getSize().y / 2));

	else if (Instance().view->getCenter().y + Instance().view->getSize().y / 2.f > MapsManager::getMainmap()->getSize().y)
		Instance().setView(sf::Vector2f(Instance().view->getCenter().x, MapsManager::getMainmap()->getSize().y - Instance().view->getSize().y / 2));

	MapsManager::getMainmap()->getMap()->setTextureRect(sf::IntRect(sf::Vector2i(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10),
		sf::Vector2i(Instance().view->getSize().x + 10, Instance().view->getSize().y + 10)));

	MapsManager::getMainmap()->getMap()->setPosition(sf::Vector2f(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10));
	MapsManager::getRadar()->update(player);
}

bool View::isOutSideView(const sf::Vector2f & position)
{
	return Instance().getViewBox().contains(position);
}

bool View::isOutSideView(const sf::FloatRect & box)
{
	return Instance().getViewBox().intersects(box);
}

sf::Vector2f View::getUpLeftCornerPosOfCurrentView()
{
	auto &view = Instance();

	return sf::Vector2f(view.view->getCenter().x - view.view->getSize().x / 2.f,
		view.view->getCenter().y - view.view->getSize().y / 2.f);
}

sf::FloatRect View::getViewBox()
{
	const sf::Vector2f viewSize = view->getSize();
	const sf::Vector2f viewPos = view->getCenter();

	return sf::FloatRect(viewPos, viewSize);
}

void View::setView(const sf::Vector2f & center)
{
	view->setCenter(center);
	Game::Instance().getWindow()->setView(*Instance().view);
}