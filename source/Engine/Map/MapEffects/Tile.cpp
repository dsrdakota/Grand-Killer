#include "Tile.hpp"

#include "../Map.hpp"

#include "../../../Manager/Texture.hpp"
#include "../../../Manager/renderSprites.hpp"
#include "../../../Manager/Tiles.hpp"

Tile::Tile(const size_t & index, const sf::Vector2f & position)
{
	sprite = new sf::Sprite(*textureManager::get(std::to_string(index)));
	sprite->setPosition(position);

	this->index = index;

	if ((index >= 1 && index <=28) ||
		(index >= 64 && index <= 76))
		tilesManager::Instance().addTileToGrassVector(this);
}

Tile::~Tile()
{
	delete sprite;
}

sf::Sprite * Tile::getTileSprite()
{
	return sprite;
}

const size_t Tile::getIndex()
{
	return index;
}

void Tile::draw()
{
	if (!Map::Instance().isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top)) ||
		!Map::Instance().isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top)) ||
		!Map::Instance().isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)) ||
		!Map::Instance().isOutsideView(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)))

		renderSprites::Instance().addToRender(sprite);
}
