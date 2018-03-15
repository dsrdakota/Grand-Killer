#include "Radar.hpp"

#include <iostream>

Radar::~Radar()
{
	delete radarArea;
	delete playerIco;
	delete target;

	delete hp;
	delete armor;
	delete third;
}

void Radar::init()
{
	radarArea = new sf::RectangleShape(sf::Vector2f(300, 150));
	radarArea->setFillColor(sf::Color(255, 0, 0, 100));

	playerIco = new sf::Sprite(*TextureManager::get("playerMinimap"));
	playerIco->setOrigin(playerIco->getGlobalBounds().left + playerIco->getGlobalBounds().width / 2.f, playerIco->getGlobalBounds().top + playerIco->getGlobalBounds().height / 2.f);

	scale = sf::Vector2f(0.1f, 0.1f);
	map->setScale(scale);

	radarView = new sf::Sprite(*map->getTexture());
	radarView2 = new sf::Sprite(*map->getTexture());

	radarView->setScale(scale);
	radarView2->setScale(scale);

	const float outlineThickness = 2;

	hpBackground = new sf::RectangleShape(sf::Vector2f(radarArea->getSize().x / 4 * 2 - outlineThickness, 8));
	hpBackground->setOutlineThickness(2);
	hpBackground->setOutlineColor(sf::Color(0, 0, 0, 220));
	hpBackground->setFillColor(sf::Color(72, 121, 68, 200));

	hp = new sf::RectangleShape(sf::Vector2f(radarArea->getSize().x / 4 * 2 - outlineThickness - 10, 8));
	hp->setFillColor(sf::Color(126, 221, 119, 200));

	armorBackground = new sf::RectangleShape(sf::Vector2f(radarArea->getSize().x / 4 * 1 - outlineThickness, 8));
	armorBackground->setOutlineThickness(2);
	armorBackground->setOutlineColor(sf::Color(0, 0, 0, 220));
	armorBackground->setFillColor(sf::Color(51, 108, 152, 200));

	armor = new sf::RectangleShape(sf::Vector2f(radarArea->getSize().x / 4 * 1 - outlineThickness - 50, 8));
	armor->setFillColor(sf::Color(75, 160, 226, 200));

	thirdBackground = new sf::RectangleShape(sf::Vector2f(radarArea->getSize().x / 4 * 1 - outlineThickness, 8));
	thirdBackground->setOutlineThickness(2);
	thirdBackground->setOutlineColor(sf::Color(0, 0, 0, 220));
	thirdBackground->setFillColor(sf::Color(131, 113, 50, 200));

	third = new sf::RectangleShape(sf::Vector2f(radarArea->getSize().x / 4 * 1 - outlineThickness - 30, 8));
	third->setFillColor(sf::Color(227, 196, 85, 200));
}

void Radar::update(IObject *player)
{
	radarView->setTexture(*map->getTexture());
	radarView2->setTexture(*map->getTexture());

	radarArea->setPosition(sf::Vector2f(View::getUpLeftCornerPosOfCurrentView().x + 40,
		View::getUpLeftCornerPosOfCurrentView().y + View::getSize().y - radarArea->getSize().y - 80));

	playerIco->setPosition(player->getPosition().x * (map->getGlobalBounds().width / size.x), player->getPosition().y * (map->getGlobalBounds().height / size.y));

	playerIco->setRotation(player->getRotation());

	map->setPosition(radarArea->getPosition());
	playerIco->setPosition(playerIco->getPosition() + radarArea->getPosition());

	centerMapOnPlayer();
}

void Radar::centerMapOnPlayer()
{
	sf::Vector2f moveOffset = sf::Vector2f(radarArea->getGlobalBounds().width / 2.f - playerIco->getPosition().x,
		radarArea->getGlobalBounds().height / 2.f - playerIco->getPosition().y);

	moveOffset += radarArea->getPosition();

	if (map->getPosition().x + moveOffset.x < radarArea->getPosition().x &&
		map->getPosition().x + map->getGlobalBounds().width + moveOffset.x > radarArea->getPosition().x + radarArea->getGlobalBounds().width)
	{
		map->move(moveOffset.x, 0);
		playerIco->move(moveOffset.x, 0);
	}

	else if(!(map->getPosition().x + map->getGlobalBounds().width + moveOffset.x > radarArea->getPosition().x + radarArea->getGlobalBounds().width))
	{
		playerIco->setPosition(playerIco->getPosition().x - radarArea->getGlobalBounds().width, playerIco->getPosition().y);
		map->setPosition(radarArea->getPosition().x + radarArea->getGlobalBounds().width - map->getGlobalBounds().width , map->getPosition().y);
	}
	

	if (map->getPosition().y + moveOffset.y < radarArea->getPosition().y &&
		map->getPosition().y + map->getGlobalBounds().height + moveOffset.y > radarArea->getPosition().y + radarArea->getGlobalBounds().height)
	{
		map->move(0, moveOffset.y);
		playerIco->move(0, moveOffset.y);
	}

	else if (!(map->getPosition().y + map->getGlobalBounds().height + moveOffset.y > radarArea->getPosition().y + radarArea->getGlobalBounds().height))
	{
		playerIco->setPosition(playerIco->getPosition().x, playerIco->getPosition().y - radarArea->getGlobalBounds().height * 3);
		map->setPosition(map->getPosition().x, radarArea->getPosition().y + radarArea->getGlobalBounds().height - map->getGlobalBounds().height);
	}

	radarView->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>((radarArea->getPosition().x - map->getPosition().x) * (size.x / map->getGlobalBounds().width)), static_cast<int>((radarArea->getPosition().y - map->getPosition().y) * (size.y / map->getGlobalBounds().height))),
		sf::Vector2i(static_cast<int>(radarArea->getGlobalBounds().width * (size.x / map->getGlobalBounds().width)), static_cast<int>(radarArea->getGlobalBounds().height * (size.y / map->getGlobalBounds().height)))));

	radarView->setPosition(radarArea->getPosition());
	radarView->setColor(sf::Color(255, 255, 255, 180));

	radarView2->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>((radarArea->getPosition().x - map->getPosition().x - 10.f) * (size.x / map->getGlobalBounds().width)), static_cast<int>((radarArea->getPosition().y - map->getPosition().y - 10.f) * (size.y / map->getGlobalBounds().height))),
		sf::Vector2i(static_cast<int>((radarArea->getGlobalBounds().width + 20.f) * (size.x / map->getGlobalBounds().width)), static_cast<int>((radarArea->getGlobalBounds().height + 20.f) * (size.y / map->getGlobalBounds().height)))));

	radarView2->setPosition(radarArea->getPosition().x - 10.f, radarArea->getPosition().y - 10.f);
	radarView2->setColor(sf::Color(255, 255, 255, 40));

	hpBackground->setPosition(radarArea->getPosition().x, radarArea->getPosition().y + radarArea->getGlobalBounds().height + 5);
	hp->setPosition(hpBackground->getPosition());

	armorBackground->setPosition(hpBackground->getPosition().x + hpBackground->getGlobalBounds().width,
		hpBackground->getPosition().y);
	armor->setPosition(armorBackground->getPosition());

	thirdBackground->setPosition(armorBackground->getPosition().x + armorBackground->getGlobalBounds().width,
		armorBackground->getPosition().y);
	third->setPosition(thirdBackground->getPosition());
}

void Radar::draw()
{
	Painter::Instance().addToDraw(radarView);
	Painter::Instance().addToDraw(radarView2);

	Painter::Instance().addToDraw(playerIco);

	Painter::Instance().addToDraw(hpBackground);
	Painter::Instance().addToDraw(hp);

	Painter::Instance().addToDraw(armorBackground);
	Painter::Instance().addToDraw(armor);

	Painter::Instance().addToDraw(thirdBackground);
	Painter::Instance().addToDraw(third);
}