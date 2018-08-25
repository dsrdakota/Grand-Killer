#include "Radar.hpp"

#include "../Game.hpp"
#include "../Engine/Engine.hpp"
#include "Minimap.hpp"
#include "GPS/GPS.hpp"
#include "ObjectsManager/MinimapIcons.hpp"

Radar::Radar() : window(Game::Instance().getWindow())
{
	radarArea = new sf::RectangleShape(sf::Vector2f(300, 150));
	radarArea->setFillColor(sf::Color(255, 0, 0, 100));

	textureOfRadar = new sf::RenderTexture;
	textureOfRadar->create(static_cast<unsigned>(Map::getMapSize().x), static_cast<unsigned>(Map::getMapSize().y));

	auto radarTiles = TilesManager::getTileRadarVector();

	scale = sf::Vector2f(0.1f, 0.1f);

	textureOfRadar->clear();

	for (int i = 0; i< TilesManager::getCountTile().y; i++)
		for (int j = 0; j < TilesManager::getCountTile().x; j++)
			textureOfRadar->draw(*radarTiles[i][j]);

	textureOfRadar->display();

	textureOfRadar->setSmooth(true);

	radar = new sf::Sprite(textureOfRadar->getTexture());

	playerIco = new sf::Sprite(*TextureManager::get("playerMinimap"));
	playerIco->setOrigin(playerIco->getGlobalBounds().left + playerIco->getGlobalBounds().width / 2.f, playerIco->getGlobalBounds().top + playerIco->getGlobalBounds().height / 2.f);

	target = new sf::Sprite(*TextureManager::get("targetMinimap"));
	target->setOrigin(target->getGlobalBounds().left + target->getGlobalBounds().width / 2.f, target->getGlobalBounds().top + target->getGlobalBounds().height / 2.f);

	radar->setScale(scale);

	radarView = new sf::Sprite(*radar->getTexture());
	radarView2 = new sf::Sprite(*radar->getTexture());

	radarView->setScale(scale);
	radarView2->setScale(scale);
	
	gps = new sf::RectangleShape(sf::Vector2f(300,150));
	gps2 = new sf::RectangleShape(sf::Vector2f(315, 165));

	const float outlineThickness = 2;

	hpBackground = new sf::RectangleShape(sf::Vector2f(radarArea->getSize().x / 4 * 2 - outlineThickness, 8));
	hpBackground->setOutlineThickness(2);
	hpBackground->setOutlineColor(sf::Color(0,0,0,220));
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

Radar::~Radar()
{
	delete radarArea;
	delete playerIco;
	delete target;

	delete hp;
	delete armor;
	delete third;
}

sf::Sprite * Radar::getRadarSprite()
{
	return Instance().radar;
}

void Radar::update(IObject *player)
{
	radarView->setTexture(*radar->getTexture());
	radarView2->setTexture(*radar->getTexture());

	radarArea->setPosition(sf::Vector2f(40, window->getSize().y - radarArea->getSize().y - 80));

	playerIco->setPosition(player->getPosition().x * (radar->getGlobalBounds().width / Map::getMapSize().x), player->getPosition().y * (radar->getGlobalBounds().height / Map::getMapSize().y));

	playerIco->setRotation(player->getRotation());

	radar->setPosition(radarArea->getPosition());
	playerIco->setPosition(playerIco->getPosition() + radarArea->getPosition());

	centerMapOnPlayer();

	if (Minimap::Instance().targetIsSet || Minimap::Instance().missionTargetIsSet)
	{
		Tile *targetTile = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Target]->getTile();
		sf::Vector2f lengthFromTile = MinimapIcons::Instance().getIcons()[(int)MinimapIconType::Target]->getLengthFromTile();

		target->setPosition(radar->getPosition().x + (targetTile->getTileMapSprite()->getPosition().x + lengthFromTile.x) * (radar->getGlobalBounds().width / Map::getMapSize().x),
			radar->getPosition().y + (targetTile->getTileMapSprite()->getPosition().y + lengthFromTile.y) * (radar->getGlobalBounds().height / Map::getMapSize().y));

		gps->setTexture(&GPS::Instance().getTextureForRadar());
		gps2->setTexture(&GPS::Instance().getTextureForRadar());
		gps2->setFillColor(sf::Color(255, 255, 255, 100));

		gps->setPosition(radarView->getPosition());
		gps2->setPosition(radarView2->getPosition());
	}
}

void Radar::centerMapOnPlayer()
{
	sf::Vector2f moveOffset = sf::Vector2f(radarArea->getGlobalBounds().width / 2.f - playerIco->getPosition().x,
		radarArea->getGlobalBounds().height / 2.f - playerIco->getPosition().y);

	moveOffset += radarArea->getPosition();

	if (radar->getPosition().x + moveOffset.x < radarArea->getPosition().x &&
		radar->getPosition().x + radar->getGlobalBounds().width + moveOffset.x > radarArea->getPosition().x + radarArea->getGlobalBounds().width)
	{
		radar->move(moveOffset.x, 0);
		playerIco->move(moveOffset.x, 0);
	}

	else if(!(radar->getPosition().x + radar->getGlobalBounds().width + moveOffset.x > radarArea->getPosition().x + radarArea->getGlobalBounds().width))
	{
		playerIco->setPosition(playerIco->getPosition().x - radarArea->getGlobalBounds().width, playerIco->getPosition().y);
		radar->setPosition(radarArea->getPosition().x + radarArea->getGlobalBounds().width - radar->getGlobalBounds().width ,radar->getPosition().y);
	}
	
	if (radar->getPosition().y + moveOffset.y < radarArea->getPosition().y &&
		radar->getPosition().y + radar->getGlobalBounds().height + moveOffset.y > radarArea->getPosition().y + radarArea->getGlobalBounds().height)
	{
		radar->move(0, moveOffset.y);
		playerIco->move(0, moveOffset.y);
	}

	else if (!(radar->getPosition().y + radar->getGlobalBounds().height + moveOffset.y > radarArea->getPosition().y + radarArea->getGlobalBounds().height))
	{
		playerIco->setPosition(playerIco->getPosition().x, playerIco->getPosition().y - radarArea->getGlobalBounds().height * 3);
		radar->setPosition(radar->getPosition().x, radarArea->getPosition().y + radarArea->getGlobalBounds().height - radar->getGlobalBounds().height);
	}

	radarView->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>((radarArea->getPosition().x - radar->getPosition().x) * (Map::getMapSize().x / radar->getGlobalBounds().width)), static_cast<int>((radarArea->getPosition().y - radar->getPosition().y) * (Map::getMapSize().y / radar->getGlobalBounds().height))),
		sf::Vector2i(static_cast<int>(radarArea->getGlobalBounds().width * (Map::getMapSize().x / radar->getGlobalBounds().width)), static_cast<int>(radarArea->getGlobalBounds().height * (Map::getMapSize().y / radar->getGlobalBounds().height)))));

	radarView->setPosition(radarArea->getPosition());
	radarView->setColor(sf::Color(255, 255, 255, 180));

	radarView2->setTextureRect(sf::IntRect(sf::Vector2i(static_cast<int>((radarArea->getPosition().x - radar->getPosition().x - 10.f) * (Map::getMapSize().x / radar->getGlobalBounds().width)), static_cast<int>((radarArea->getPosition().y - radar->getPosition().y - 10.f) * (Map::getMapSize().y / radar->getGlobalBounds().height))),
		sf::Vector2i(static_cast<int>((radarArea->getGlobalBounds().width + 20.f) * (Map::getMapSize().x / radar->getGlobalBounds().width)), static_cast<int>((radarArea->getGlobalBounds().height + 20.f) * (Map::getMapSize().y / radar->getGlobalBounds().height)))));

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
	//Painter::Instance().addToInterfaceDraw(radar);
	Painter::Instance().addToInterfaceDraw(radarView);
	Painter::Instance().addToInterfaceDraw(radarView2);

	if (Minimap::Instance().isTargetSet() || Minimap::Instance().missionTargetIsSet)
	{
		Painter::Instance().addToInterfaceDraw(gps);
		Painter::Instance().addToInterfaceDraw(gps2);
	}

	if (Minimap::Instance().isTargetSet() && radarView->getGlobalBounds().contains(target->getPosition()))
		Painter::Instance().addToInterfaceDraw(target);

	Painter::Instance().addToInterfaceDraw(playerIco);

	Painter::Instance().addToInterfaceDraw(hpBackground);
	Painter::Instance().addToInterfaceDraw(hp);

	Painter::Instance().addToInterfaceDraw(armorBackground);
	Painter::Instance().addToInterfaceDraw(armor);

	Painter::Instance().addToInterfaceDraw(thirdBackground);
	Painter::Instance().addToInterfaceDraw(third);
}
