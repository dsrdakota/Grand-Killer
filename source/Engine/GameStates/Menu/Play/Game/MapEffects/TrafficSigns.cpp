#include "TrafficSigns.hpp"

#include "../../../../../../Manager/texture.hpp"
#include "../../../../../../Manager/renderSprites.hpp"

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

void TrafficSigns::drawUnder()
{
	for (auto i = 0;i < 5;++i)
		signs[i].checkCollision();

	for(auto i=0;i<5;++i)
		if (signs[i].getDrawState() == -1) // -1 Under
		{
			renderSprites::Instance().addToRender(signs[i].getSignSprite());
			renderSprites::Instance().addToRender(signs[i].getSignHitbox());
		}
}

void TrafficSigns::drawOn()
{
	for (auto i = 0;i < 5;++i)
		signs[i].checkCollision();

	for (auto i = 0;i<5;++i)
		if (signs[i].getDrawState() == 1) // 1 On
		{
			renderSprites::Instance().addToRender(signs[i].getSignSprite());
			renderSprites::Instance().addToRender(signs[i].getSignHitbox());
		}
}
