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
	const sf::Vector2f &getTargetPos();

	void setPosition();
	void setPlayerPosition(Tile *playerTile, const sf::Vector2f &lengthPlayerFromTileOrigin, const float &rot);
	void show(bool fromMenu = false);

	bool canExitMinimap();
	bool canRunMinimap();
	void resetCooldown();

private:

	sf::RenderWindow *window;

	sf::Sprite *map;
	sf::RectangleShape *mapArea;
	std::vector<std::vector<Tile*>>mapTiles;

	sf::Sprite *player;
	sf::Sprite *target;
	sf::Sprite *cursor; // to change !!!
	std::vector<sf::RectangleShape*>tag;
	sf::CircleShape *centerOfTag;

	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	Tile *playerTile;
	sf::Vector2f lengthPlayerFromTileOrigin;
	float playerRotation;

	Tile *targetTile;
	sf::Vector2f lengthTargetFromTileOrigin;

	sf::Vector2f scale;
	const sf::Vector2f *minScale;
	const sf::Vector2f *maxScale;

	sf::RectangleShape *background;

	Time time;
	Time cooldown;

	int playerIsVisible;
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

	void setPlayerVisible();
	void setTarget();

	friend class MapInMenu;
	friend class GPS;
};