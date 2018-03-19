#pragma once

#include <SFML/Graphics.hpp>

#include "../../States.hpp"
#include "../../../../../../Map/Map.hpp"
#include "../../../../../../Engine/Engine.hpp"

class MapInMenu : public MenuStates
{
public:

	MapInMenu();
	~MapInMenu();

	void setPosition(const sf::Vector2f &menuPos, const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	bool isActive() override;
	void drawActive() override;
	void drawUnactive() override;

	void setPlayerPosition(Tile *playerTile, const sf::Vector2f &lengthPlayerFromTileOrigin, const float &rot);

private:

	sf::Sprite *map;
	sf::RectangleShape *mapArea;
	std::vector<std::vector<Tile*>>mapTiles;

	sf::Sprite *player;
	sf::Sprite *target;

	std::vector<std::pair<Text*, sf::Sprite*>>navigation;

	Tile *playerTile;
	sf::Vector2f lengthPlayerFromTileOrigin;
	float playerRotation;

	Tile *targetTile;
	sf::Vector2f lengthTargetFromTileOrigin;

	sf::Vector2f menuPos;
	sf::Vector2f scale;

	bool active;

	bool mouseOnMap();
	void updateIcons();
	void setTilesScale();
	void cutTiles();
	void draw();

	void setTarget();
};