#include "SwimmingPool.hpp"
#include "../../../../../../Manager/Texture.hpp"
#include "../../../../../../Manager/renderSprites.hpp"

SwimmingPool::SwimmingPool()
{
	countOfTexture = 0;

	for (auto i = 0;i < 10;++i)
		textureManager::load("swimmingPool" + std::to_string(i),"data/Map/SwimmingPool/"+std::to_string(i) + ".png");

	swimmingPool = new sf::Sprite(*textureManager::get("swimmingPool" + std::to_string(0)));
	swimmingPool->setPosition(282, 1299);
}

SwimmingPool::~SwimmingPool()
{
	delete swimmingPool;
}

void SwimmingPool::draw()
{
	if (clock.time->asMilliseconds() > 60)
	{
		countOfTexture++;
		if (countOfTexture >= 10)
			countOfTexture = 0;

		swimmingPool->setTexture(*textureManager::get("swimmingPool" + std::to_string(countOfTexture)));

		clock.clock->restart();
		*clock.time = sf::Time::Zero;
	}
		renderSprites::Instance().addToRender(swimmingPool);
}
