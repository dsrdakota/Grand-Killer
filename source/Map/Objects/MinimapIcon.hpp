#pragma once

#include <SFML/Graphics.hpp>

#include "../../Engine/Engine.hpp"

#include "../ObjectsManager/Tiles.hpp"

enum class MinimapIconType
{
	Player,
	Target,
	MissionTarget,
};

class MinimapIcon
{
public:

	bool drawable = true;
	bool blink = false;
	bool alwaysVisible = false;

	MinimapIcon(const MinimapIconType &type, const sf::Vector2f &position = sf::Vector2f(0, 0), const float &angle = 0);
	~MinimapIcon();

	const MinimapIconType &getType();

	sf::Sprite *getSprite();
	const sf::Vector2f &getPosition();

	Tile *getTile();
	const sf::Vector2f &getLengthFromTile();

	void setPosition(const sf::Vector2f &position);
	void setPosition(Tile *tile, const sf::Vector2f &lengthFromTile);

	void setRotation(const float &angle);

	void updatePosition(const sf::Vector2f& scale = sf::Vector2f(1, 1));
	void draw();

private:

	MinimapIconType type;

	sf::Sprite *icon;
	Tile *tile;
	sf::Vector2f lengthFromTile;
	
	Time time;
	int visibleCooldown;

	sf::Vector2f position;
	float rotation;

	void doBlink();
	Tile *getTileUnderPosition(const sf::Vector2f &position);

	std::string typeToString(const MinimapIconType &type);
};