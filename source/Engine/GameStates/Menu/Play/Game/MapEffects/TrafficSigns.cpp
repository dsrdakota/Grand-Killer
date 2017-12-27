#include "TrafficSigns.hpp"

#include "../../../../../../Manager/texture.hpp"
#include "../../../../../../Manager/renderSprites.hpp"

TrafficSigns::TrafficSigns()
{
	textureManager::load("sign", "data/Map/Traffic/Sign/stop.png");
	signs = new Sign[5];
	signs[0].setPosition(sf::Vector2f(3943, 4631));
}

TrafficSigns::~TrafficSigns()
{
	delete[]signs;
}

void TrafficSigns::drawUnder()
{
	signs[0].checkCollision();

	for(auto i=0;i<5;++i)
		if (signs[i].getDrawState() == -1) // -1 Under
		{
			renderSprites::Instance().addToRender(signs[i].getSignSprite());
			renderSprites::Instance().addToRender(signs[i].getSignHitbox());
		}
}

void TrafficSigns::drawOn()
{
	signs[0].checkCollision();

	for (auto i = 0;i<5;++i)
		if (signs[i].getDrawState() == 1) // 1 On
		{
			renderSprites::Instance().addToRender(signs[i].getSignSprite());
			renderSprites::Instance().addToRender(signs[i].getSignHitbox());
		}
}
