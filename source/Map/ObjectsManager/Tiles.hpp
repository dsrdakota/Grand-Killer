#pragma once

#include <SFML/Graphics.hpp>

class Tiles
{
public:

	~Tiles();
	
	Tiles(const Tiles &) = delete;
	void operator=(const Tiles &) = delete;

	inline static Tiles& Instance()
	{
		static Tiles tiles;
		return tiles;
	}

	enum class Types{
		asphalt,
		asphalt_grass_corner_in_BL,
		asphalt_grass_corner_in_BR,
		asphalt_grass_corner_in_TL,
		asphalt_grass_corner_in_TR,
		asphalt_grass_corner_out_BL,
		asphalt_grass_corner_out_BR,
		asphalt_grass_corner_out_TL,
		asphalt_grass_corner_out_TR,
		asphalt_grass_hor_border_BOTT,
		asphalt_grass_hor_border_LEFT,
		asphalt_grass_hor_border_RIGHT,
		asphalt_grass_hor_border_TOP,
		asphalt_grass_hor_pedlanes_BL,
		asphalt_grass_hor_pedlanes_BR,
		asphalt_grass_hor_pedlanes_TL,
		asphalt_grass_hor_pedlanes_TR,
		asphalt_grass_pvmt_hor_border_BL,
		asphalt_grass_pvmt_hor_border_BR,
		asphalt_grass_pvmt_hor_border_TL,
		asphalt_grass_pvmt_hor_border_TR,
		asphalt_grass_pvmt_vert_border_BL,
		asphalt_grass_pvmt_vert_border_BR,
		asphalt_grass_pvmt_vert_border_TL,
		asphalt_grass_pvmt_vert_border_TR,
		asphalt_grass_vert_pedlanes_BL,
		asphalt_grass_vert_pedlanes_BR,
		asphalt_grass_vert_pedlanes_TL,
		asphalt_grass_vert_pedlanes_TR,
		asphalt_hor_lane_LEFT,
		asphalt_hor_lane_RIGHT,
		asphalt_hor_pedlanes,
		asphalt_hor_pedlanes_LEFT,
		asphalt_hor_pedlanes_RIGHT,
		asphalt_manhole,
		asphalt_pavement_corner_in_BL,
		asphalt_pavement_corner_in_BR,
		asphalt_pavement_corner_in_TL,
		asphalt_pavement_corner_in_TR,
		asphalt_pavement_corner_out_BL,
		asphalt_pavement_corner_out_BR,
		asphalt_pavement_corner_out_TL,
		asphalt_pavement_corner_out_TR,
		asphalt_pavement_hor_border_BOTT,
		asphalt_pavement_hor_border_pedlanes_BOTT,
		asphalt_pavement_hor_border_pedlanes_TL,
		asphalt_pavement_hor_border_pedlanes_TOP,
		asphalt_pavement_hor_border_TOP,
		asphalt_pavement_hor_pedlanes_BL,
		asphalt_pavement_hor_pedlanes_BR,
		asphalt_pavement_hor_pedlanes_TR,
		asphalt_pavement_vert_border_LEFT,
		asphalt_pavement_vert_border_pedlanes_LEFT,
		asphalt_pavement_vert_border_pedlanes_RIGHT,
		asphalt_pavement_vert_border_RIGHT,
		asphalt_pavement_vert_pedlanes_BL,
		asphalt_pavement_vert_pedlanes_BR,
		asphalt_pavement_vert_pedlanes_TL,
		asphalt_pavement_vert_pedlanes_TR,
		asphalt_vert_lane_BOTT,
		asphalt_vert_lane_TOP,
		asphalt_vert_pedlanes,
		asphalt_vert_pedlanes_BOTT,
		asphalt_vert_pedlanes_TOP,
		grass,
		grass_pavement_corner_in_BL,
		grass_pavement_corner_in_BR,
		grass_pavement_corner_in_TL,
		grass_pavement_corner_in_TR,
		grass_pavement_corner_out_BL,
		grass_pavement_corner_out_BR,
		grass_pavement_corner_out_TL,
		grass_pavement_corner_out_TR,
		grass_pavement_hor_border_BOTT,
		grass_pavement_hor_border_TOP,
		grass_pavement_vert_border_LEFT,
		grass_pavement_vert_border_RIGHT,
		pavement,
	};

	static std::string getTypeAsString(const Types &type);
	static sf::Vector2u getTilesCount();
	static sf::Vector2u getTileSize();

private:

	Tiles();

	sf::Vector2u tileSize;
	sf::Vector2u tilesCount;

};