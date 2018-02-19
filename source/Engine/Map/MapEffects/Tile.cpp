#include "Tile.hpp"

#include "../Map.hpp"

#include "../../../Manager/Texture.hpp"
#include "../../../Manager/renderSprites.hpp"
#include "../../../Manager/Tiles.hpp"

Tile::Tile(const size_t & index, const sf::Vector2f & position)
{
	sprite = new sf::Sprite(*textureManager::get(std::to_string(index)));
	sprite->setPosition(position);

	mapSprite = new sf::Sprite(*textureManager::get(std::to_string(index) + "_Minimap"));

	radarSprite = new sf::Sprite(*textureManager::get(std::to_string(index) + "_Minimap"));
}

Tile::~Tile()
{
	delete sprite;
}

sf::Sprite * Tile::getTileSprite()
{
	return sprite;
}

sf::Sprite * Tile::getTileMapSprite()
{
	return mapSprite;
}

sf::Sprite * Tile::getTileRadarSprite()
{
	return radarSprite;
}

const size_t Tile::getIndex()
{
	return index;
}
