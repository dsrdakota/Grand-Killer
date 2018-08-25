#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Engine.hpp"
#include "ObjectsManager/Tiles.hpp"
#include "../States/Play/Game/Menu/States/MapInMenu/MapInMenu.hpp"

class Minimap
{
public:

	~Minimap();

	Minimap(const Minimap &) = delete;
	void operator=(const Minimap &) = delete;

	inline static Minimap& Instance()
	{
		static Minimap minimap;
		return minimap;
	}

	const bool isTargetSet();

	void setPosition();
	void setMissionTargetPosition(const sf::Vector2f &globalPosition);
	void setPlayerPosition(const sf::Vector2f &globalPosition, const float &angle);
	void show(bool fromMenu = false);

	bool canExitMinimap();
	bool canRunMinimap();
	void resetCooldown();

private:

	sf::RenderWindow *window;

	sf::Sprite *map;
	sf::RectangleShape *mapArea;
	std::vector<std::vector<Tile*>>mapTiles;

	sf::Sprite *cursor; // to change !!!
	std::vector<sf::RectangleShape*>tag;
	sf::CircleShape *centerOfTag;

	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	sf::Vector2f scale;
	const sf::Vector2f *minScale;
	const sf::Vector2f *maxScale;

	sf::RectangleShape *background;

	Time cooldown;

	bool missionTargetIsSet;

	bool targetIsSet;
	bool canSetTarget;

	Minimap();

	void toControl();
	bool mouseOnMap();
	Tile *getCenterTileOnWindow();
	Tile *getTileUnderMouse();
	Tile *getTileUnderPosition(const sf::Vector2f &position);
	void centerMapOnTile(sf::Sprite *tileSprite, const sf::Vector2f &lengthFromTile);
	void centerMapOnPlayer();
	void moveAllTiles(const sf::Vector2f &offset);
	void updateIcons();
	void setTilesScale();

	void setGPSOnMinimap();

	friend class MapInMenu;
	friend class GPS;
	friend class Radar;
};