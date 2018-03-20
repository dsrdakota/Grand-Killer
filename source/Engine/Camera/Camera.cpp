#include "Camera.hpp"

#include "../../Map/Map.hpp"
#include "../../Map/Radar.hpp"
#include "../GlobalSettings/GlobalSettings.hpp"
#include "../Rendering/Painter.hpp"

Camera::Camera()
{
	view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(static_cast<float>(GlobalSettings::getWidth()), static_cast<float>(GlobalSettings::getHeight())));
	viewBox = new sf::RectangleShape(view->getSize());
	viewBox->setOrigin(view->getSize().x / 2.f, view->getSize().y / 2.f);
}

Camera::~Camera()
{
	delete view;
	delete viewBox;
}

sf::View * Camera::getView() const
{
	return view;
}

void Camera::updateView(IObject *player)
{
	Instance().setView(player);

	if (Instance().viewBox->getGlobalBounds().left < 0)
		Instance().setView(sf::Vector2f(Instance().view->getSize().x / 2, Instance().view->getCenter().y));

	else if (Instance().view->getCenter().x + Instance().view->getSize().x / 2 > Map::getMapSize().x)
		Instance().setView(sf::Vector2f(Map::getMapSize().x - Instance().view->getSize().x / 2, Instance().view->getCenter().y));

	if (Instance().view->getCenter().y - Instance().view->getSize().y / 2 < 0)
		Instance().setView(sf::Vector2f(Instance().view->getCenter().x, Instance().view->getSize().y / 2));

	else if (Instance().view->getCenter().y + Instance().view->getSize().y / 2.f > Map::getMapSize().y)
		Instance().setView(sf::Vector2f(Instance().view->getCenter().x, Map::getMapSize().y - Instance().view->getSize().y / 2));

	Map::getMap()->setTextureRect(sf::IntRect(sf::Vector2i(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10),
		sf::Vector2i(Instance().view->getSize().x + 10, Instance().view->getSize().y + 10)));
	
	Map::getMap()->setPosition(sf::Vector2f(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10));
	
	Radar::Instance().update(player);
}

bool Camera::isOutsideView(const sf::Vector2f & position)
{
	return !Instance().viewBox->getGlobalBounds().contains(position);
}

bool Camera::isOutsideView(const sf::FloatRect & box)
{
	return !Instance().viewBox->getGlobalBounds().intersects(box);
}

void Camera::draw()
{
	Painter::Instance().addToDraw(Instance().viewBox);
}

sf::Vector2f Camera::getUpLeftCornerPosOfCurrentView()
{
	auto &view = Instance();

	return sf::Vector2f(view.view->getCenter().x - view.view->getSize().x / 2.f,
		view.view->getCenter().y - view.view->getSize().y / 2.f);
}

void Camera::setView(IObject * player)
{
	view->setCenter(player->getPosition());
	viewBox->setPosition(player->getPosition());
	Game::Instance().getWindow()->setView(*Instance().view);
}

void Camera::setView(const sf::Vector2f & center)
{
	view->setCenter(center);
	viewBox->setPosition(center);
	Game::Instance().getWindow()->setView(*Instance().view);
}