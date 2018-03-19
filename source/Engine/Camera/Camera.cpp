#include "Camera.hpp"

#include "../../Map/Map.hpp"
#include "../GlobalSettings/GlobalSettings.hpp"

Camera::Camera()
{
	view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(static_cast<float>(GlobalSettings::getWidth()), static_cast<float>(GlobalSettings::getHeight())));
}

Camera::~Camera()
{
	delete view;
}

/*sf::View * View::getView()
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

	//MapsManager::getMainmap()->getMap()->setTextureRect(sf::IntRect(sf::Vector2i(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10),
		//sf::Vector2i(Instance().view->getSize().x + 10, Instance().view->getSize().y + 10)));
	
	//MapsManager::getMainmap()->getMap()->setPosition(sf::Vector2f(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10));
	MapsManager::getRadar()->update(player);
}*/

bool Camera::isOutSideView(const sf::Vector2f & position)
{
	return !Instance().getViewBox().contains(position);
}

bool Camera::isOutSideView(const sf::FloatRect & box)
{
	return !Instance().getViewBox().intersects(box);
}

/*sf::Vector2f View::getUpLeftCornerPosOfCurrentView()
{
	auto &view = Instance();

	return sf::Vector2f(view.view->getCenter().x - view.view->getSize().x / 2.f,
		view.view->getCenter().y - view.view->getSize().y / 2.f);
}*/

sf::FloatRect Camera::getViewBox()
{
	const sf::Vector2f viewSize = Map::Instance().getView()->getSize();
	const sf::Vector2f viewPos = Map::Instance().getUpLeftCornerPosOfCurrentView();

	return sf::FloatRect(viewPos, viewSize);
}

void Camera::setView(const sf::Vector2f & center)
{
	view->setCenter(center);
	Game::Instance().getWindow()->setView(*Instance().view);
}