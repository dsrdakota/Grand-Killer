#include "TrafficSigns.hpp"

#include "../../../Manager/Texture.hpp"
#include "../../../Manager/renderSprites.hpp"
#include "../Map.hpp"

TrafficSigns::TrafficSigns()
{
	textureManager::load("sign", "data/Map/Traffic/Sign/stop.png");
	signs = new Sign[5];
	signs[0].setPosition(sf::Vector2f(3943, 4631));
	signs[1].setPosition(sf::Vector2f(820, 1915),180);
	signs[2].setPosition(sf::Vector2f(5216,2265),90);
	signs[3].setPosition(sf::Vector2f(3404,2759),-90);
	signs[4].setPosition(sf::Vector2f(3061,3890),90);
}

TrafficSigns::~TrafficSigns()
{
	delete[]signs;
}

std::vector<sf::CircleShape*> TrafficSigns::getAllSignsHitbox()
{
	std::vector<sf::CircleShape*> hitboxes;
	for (auto i = 0;i < 5;++i)
		hitboxes.push_back(signs->getSignHitbox());

	return hitboxes;
}

void TrafficSigns::drawUnder()
{
	for (auto i = 0;i < 5;++i)
	{
		signs[i].checkCollision();
		if (signs[i].getDrawState() == -1)
		{
			if (!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left, signs[i].getSignSprite()->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left + signs[i].getSignSprite()->getGlobalBounds().width, signs[i].getSignSprite()->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left + signs[i].getSignSprite()->getGlobalBounds().width, signs[i].getSignSprite()->getGlobalBounds().top + signs[i].getSignSprite()->getGlobalBounds().height)) ||
				!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left, signs[i].getSignSprite()->getGlobalBounds().top + signs[i].getSignSprite()->getGlobalBounds().height)))
				renderSprites::Instance().addToRender(signs[i].getSignSprite());
		}
	}
}

void TrafficSigns::drawOn()
{
	for (auto i = 0;i<5;++i)
		if (signs[i].getDrawState() == 1)
		{
			if (!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left, signs[i].getSignSprite()->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left + signs[i].getSignSprite()->getGlobalBounds().width, signs[i].getSignSprite()->getGlobalBounds().top)) ||
				!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left + signs[i].getSignSprite()->getGlobalBounds().width, signs[i].getSignSprite()->getGlobalBounds().top + signs[i].getSignSprite()->getGlobalBounds().height)) ||
				!Map::isOutsideView(sf::Vector2f(signs[i].getSignSprite()->getGlobalBounds().left, signs[i].getSignSprite()->getGlobalBounds().top + signs[i].getSignSprite()->getGlobalBounds().height)))
				renderSprites::Instance().addToRender(signs[i].getSignSprite());
		}
}
