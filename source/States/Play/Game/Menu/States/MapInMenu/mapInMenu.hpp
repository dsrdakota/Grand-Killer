#pragma once

#include <SFML/Graphics.hpp>

#include "../../States.hpp"
#include "../../../../../../Map/Map.hpp"

class MapInMenu : public MenuStates
{
public:

	MapInMenu();
	~MapInMenu();

	void setPosition(const sf::Vector2f &borderXrange, const sf::Vector2f &borderYrange) override;
	bool exit() override;
	bool isActive() override;
	void drawActive() override;
	void drawUnactive() override;

private:

	sf::Sprite *map;
	sf::Sprite *cuttedMap;
	sf::RenderTexture *cuttedMapTexture;
	sf::RectangleShape *mapArea;

	sf::Sprite *player;
	sf::Sprite *target;

	bool active;

	bool mouseOnMap();
	void cutMap();
};