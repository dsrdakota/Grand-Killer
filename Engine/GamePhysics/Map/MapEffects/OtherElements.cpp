#include "OtherElements.hpp"
#include "../../../../Manager/Texture.hpp"
#include "../../../../Manager/renderSprites.hpp"
#include "../Map.hpp"

Other::Other()
{
	leaves = new sf::Sprite[4];
	roofs = new sf::Sprite[2];

	for (auto i = 0;i < 4;++i)
		leaves[i].setTexture(*textureManager::load("leaves" + std::to_string(i), "data/Map/Other/leaves" + std::to_string(i + 1) + ".png"));

	for (auto i = 0;i < 2;++i)
		roofs[i].setTexture(*textureManager::load("roof" + std::to_string(i), "data/Map/Other/roof" + std::to_string(i + 1) + ".png"));

	leaves[0].setPosition(3760, 5091);
	leaves[1].setPosition(1362, 520);
	leaves[2].setPosition(573, 973);
	leaves[3].setPosition(5504, 5420);

	roofs[0].setPosition(396, 464);
	roofs[1].setPosition(731,601);
}

Other::~Other()
{
	delete[]leaves;
	delete[]roofs;
}

void Other::draw()
{
	for (auto i = 0;i < 4;++i)
		if (!Map::isOutsideView(sf::Vector2f(leaves[i].getGlobalBounds().left, leaves[i].getGlobalBounds().top)) ||
			!Map::isOutsideView(sf::Vector2f(leaves[i].getGlobalBounds().left + leaves[i].getGlobalBounds().width, leaves[i].getGlobalBounds().top)) ||
			!Map::isOutsideView(sf::Vector2f(leaves[i].getGlobalBounds().left + leaves[i].getGlobalBounds().width, leaves[i].getGlobalBounds().top + leaves[i].getGlobalBounds().height)) ||
			!Map::isOutsideView(sf::Vector2f(leaves[i].getGlobalBounds().left, leaves[i].getGlobalBounds().top + leaves[i].getGlobalBounds().height)))
			renderSprites::Instance().addToRender(&leaves[i]);

	for (auto i = 0;i < 2;++i)
		if (!Map::isOutsideView(sf::Vector2f(roofs[i].getGlobalBounds().left, roofs[i].getGlobalBounds().top)) ||
			!Map::isOutsideView(sf::Vector2f(roofs[i].getGlobalBounds().left + roofs[i].getGlobalBounds().width, roofs[i].getGlobalBounds().top)) ||
			!Map::isOutsideView(sf::Vector2f(roofs[i].getGlobalBounds().left + roofs[i].getGlobalBounds().width, roofs[i].getGlobalBounds().top + roofs[i].getGlobalBounds().height)) ||
			!Map::isOutsideView(sf::Vector2f(roofs[i].getGlobalBounds().left, roofs[i].getGlobalBounds().top + roofs[i].getGlobalBounds().height)))
		renderSprites::Instance().addToRender(&roofs[i]);
}
