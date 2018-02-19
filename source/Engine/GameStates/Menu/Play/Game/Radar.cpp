#include "Radar.hpp"

#include "../../../../../Game.hpp"
#include "../../../../../Manager/renderSprites.hpp"
#include "../../../../../Manager/Texture.hpp"

#include <iostream>

Radar::Radar() : window(Game::Instance().getWindow())
{
	radarArea = new sf::RectangleShape(sf::Vector2f(300, 150));
	radarArea->setFillColor(sf::Color(255, 0, 0, 100));

	radar = Map::getRadar();

	player = new sf::Sprite(*textureManager::get("playerMinimap"));
	player->setOrigin(player->getGlobalBounds().left + player->getGlobalBounds().width / 2.f, player->getGlobalBounds().top + player->getGlobalBounds().height / 2.f);

	scale = sf::Vector2f(0.1f, 0.1f);
	radar->setScale(scale);
}

Radar::~Radar()
{
	delete radarArea;
	delete player;
	delete target;
}

void Radar::update(const sf::Vector2f &position, const float &rotation)
{
	radar = Map::getRadar();

	radarArea->setPosition(sf::Vector2f(Map::getUpLeftCornerPosOfCurrentView().x + 40,
		Map::getUpLeftCornerPosOfCurrentView().y + window->getSize().y - radarArea->getSize().y - 80));

	player->setPosition(position.x * (radar->getGlobalBounds().width / 6000), position.y * (radar->getGlobalBounds().height / 6000));

	player->setRotation(rotation);

	radar->setPosition(radarArea->getPosition());
	player->setPosition(player->getPosition() + radarArea->getPosition());

	centerMapOnPlayer();
}

void Radar::centerMapOnPlayer()
{
	sf::Vector2f moveOffset = sf::Vector2f(radarArea->getGlobalBounds().width / 2.f - player->getPosition().x,
		radarArea->getGlobalBounds().height / 2.f - player->getPosition().y);

	radar->move(moveOffset + radarArea->getPosition());
	player->move(moveOffset + radarArea->getPosition());
}

void Radar::draw()
{
	renderSprites::Instance().addToRender(radar);
	renderSprites::Instance().addToRender(radarArea);

	renderSprites::Instance().addToRender(player);
}