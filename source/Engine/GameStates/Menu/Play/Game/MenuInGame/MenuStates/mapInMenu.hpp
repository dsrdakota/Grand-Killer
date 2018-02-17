#pragma once

#include <SFML/Graphics.hpp>

#include "../menuStates.hpp"
#include "../../../../../../Map/Map.hpp"
#include "../../../../../../../Manager/Button.hpp"
#include "../../../../../../../Manager/Keyboard.hpp"
#include "../../../../../../../Manager/Text.hpp"
#include "../../../../../../../Manager/Time.hpp"

class mapInMenu : public menuStates
{
public:

	mapInMenu();
	~mapInMenu();

	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	bool isActive() override;
	void drawActive() override;
	void drawUnactive() override;

	void setPlayerPosition(Tile *playerTile, const sf::Vector2f &lengthFromTileOrigin, const float &rot);

private:

	sf::RectangleShape *map;
	std::vector<std::vector<Tile*>>mapTiles;

	sf::Sprite *player;
	sf::Sprite *target;
	sf::Sprite *cursor; // to change !!!
	std::vector<sf::RectangleShape*>tag;
	sf::CircleShape *centerOfTag;

	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	Tile *playerTile;
	sf::Vector2f lengthFromTileOrigin;
	float playerRotation;
	sf::Vector2f targetPosition;
	sf::Vector2f menuPos;

	sf::Vector2f scale;
	const sf::Vector2f *minScale;
	const sf::Vector2f *maxScale;
	sf::Vector2f mapSizeActive;
	sf::Vector2f mapSizeUnactive;
	sf::Vector2f mapPosUnactive;

	Time time;
	int playerIsVisible;
	bool active;
	bool targetIsSet;
	bool canSetTarget;

	void toControl();
	bool mouseOnMap();
	Tile *getCenterTileOnWindow();
	void centerMapOnTile(sf::Sprite *tileSprite,const sf::Vector2f &lengthFromTile);
	void centerMapOnPlayer();
	void moveAllTiles(const sf::Vector2f &offset);
	void updateIcons();
	void setTilesScale();
	void cutTiles();
	void draw();

	void setPlayerVisible();
	void setTarget();

};