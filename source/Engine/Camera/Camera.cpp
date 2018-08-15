#include "Camera.hpp"

#include "../../Map/Map.hpp"
#include "../../Map/Radar.hpp"
#include "../Engine.hpp"

#include "../../IObject/Player/Player.hpp"
#include "../../Car/Car.hpp"

Camera::Camera()
{
	scale = 0.9f;

	view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(static_cast<float>(GlobalSettings::getWidth()) * scale, static_cast<float>(GlobalSettings::getHeight() * scale)));
}

Camera::~Camera()
{
	delete view;
}

sf::View * Camera::getView() const
{
	return view;
}

void Camera::updateView(IObject *player)
{
	sf::Vector2f moveOffset = player->getPosition() - Instance().view->getCenter();
	Instance().view->move(moveOffset * 0.085f);

	Instance().setViewScale(player);

	if (Instance().view->getCenter().x - Instance().view->getSize().x / 2 < 0)
		Instance().view->setCenter(sf::Vector2f(Instance().view->getSize().x / 2, Instance().view->getCenter().y));

	else if (Instance().view->getCenter().x + Instance().view->getSize().x / 2 > Map::getMapSize().x)
		Instance().view->setCenter(sf::Vector2f(Map::getMapSize().x - Instance().view->getSize().x / 2, Instance().view->getCenter().y));

	if (Instance().view->getCenter().y - Instance().view->getSize().y / 2 < 0)
		Instance().view->setCenter(sf::Vector2f(Instance().view->getCenter().x, Instance().view->getSize().y / 2));

	else if (Instance().view->getCenter().y + Instance().view->getSize().y / 2.f > Map::getMapSize().y)
		Instance().view->setCenter(sf::Vector2f(Instance().view->getCenter().x, Map::getMapSize().y - Instance().view->getSize().y / 2));

	Map::getMap()->setTextureRect(sf::IntRect(sf::Vector2i(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10),
		sf::Vector2i(Instance().view->getSize().x + 10, Instance().view->getSize().y + 10)));

	Map::getMap()->setPosition(sf::Vector2f(Instance().view->getCenter().x - Instance().view->getSize().x / 2 - 10, Instance().view->getCenter().y - Instance().view->getSize().y / 2 - 10));
	
	Radar::Instance().update(player);

	Game::Instance().getWindow()->setView(*Instance().view);
}

bool Camera::isOutsideView(const sf::Vector2f & position)
{
	return !Instance().getViewRect().contains(position);
}

bool Camera::isOutsideView(const sf::FloatRect & box)
{
	return !Instance().getViewRect().intersects(box);
}

const sf::FloatRect Camera::getViewRect() const
{
	return sf::FloatRect(sf::Vector2f(Instance().view->getCenter().x - Instance().view->getSize().x / 2, Instance().view->getCenter().y - Instance().view->getSize().y / 2),
		sf::Vector2f(Instance().view->getSize().x + 20, Instance().view->getSize().y + 20));
}

void Camera::setViewScale(IObject * player)
{
	float newScale;
	const float SPEED_SCALING = 0.3f;

	if (player->getCar() != nullptr)
	{
		if (player->getCar()->getSpeed() > 5.f)
		{
			newScale = 0.9f + ((static_cast<float>(player->getCar()->getSpeed()) - 5.f) * 0.1f) / (static_cast<float>(player->getCar()->getMaxSpeed()) / 3.f);

			if (scale != newScale)
			{
				if (scale > newScale)
				{
					if (scale - SPEED_SCALING >= newScale)
						scale -= SPEED_SCALING;
					else
						scale = newScale;
				}
				else
				{
					if (scale + SPEED_SCALING <= newScale)
						scale += SPEED_SCALING;
					else
						scale = newScale;
				}

				sf::Vector2f newSize = sf::Vector2f(static_cast<float>(GlobalSettings::getWidth())* scale, static_cast<float>(GlobalSettings::getHeight()) * scale);

				view->setSize(newSize);
			}
		}
		else
		{
			newScale = 0.9f + (static_cast<float>(player->getCar()->getSpeed()) * 0.1f) / (static_cast<float>(player->getCar()->getMaxSpeed()) / 3.f);
			
			if (scale > newScale)
			{
				if (scale - SPEED_SCALING >= newScale)
					scale -= SPEED_SCALING;
				else
					scale = newScale;

				sf::Vector2f newSize = sf::Vector2f(static_cast<float>(GlobalSettings::getWidth())* scale, static_cast<float>(GlobalSettings::getHeight()) * scale);

				view->setSize(newSize);
			}
		}
	}
}