#include "MenuInGame.hpp"

#include "../../../../../../Manager/renderSprites.hpp"

MenuInGame::MenuInGame(const sf::Vector2u &windowSize)
{
	background = new sf::RectangleShape(static_cast<sf::Vector2f>(windowSize));
	background->setFillColor(sf::Color(0, 102, 51, 120));
}

MenuInGame::~MenuInGame()
{
	delete background;
}

void MenuInGame::draw(const sf::Vector2f &menuPos)
{
	background->setPosition(menuPos);
	renderSprites::Instance().addToRender(background);
}
