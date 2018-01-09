#include "MenuInGame.hpp"

#include "../../../../../../Manager/renderSprites.hpp"

MenuInGame::MenuInGame(const sf::Vector2u &windowSize)
{
	background = new sf::RectangleShape(static_cast<sf::Vector2f>(windowSize));
	background->setFillColor(sf::Color(0, 102, 51, 200));

	cooldown = 2;
}

MenuInGame::~MenuInGame()
{
	delete background;
}

void MenuInGame::updateCooldown()
{
	if (time.time->asSeconds() >= 1)
	{
		cooldown--;
		time.clock->restart();
		*time.time = sf::Time::Zero;
	}
}

void MenuInGame::restartCooldownValue()
{
	cooldown = 2;
}

void MenuInGame::setPosition(const sf::Vector2f & menuPos)
{
	background->setPosition(menuPos);
}

const int & MenuInGame::getCooldownValue()
{
	return cooldown;
}

void MenuInGame::draw()
{
	renderSprites::Instance().addToRender(background);
}
