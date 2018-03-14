#pragma once

#include "../States.hpp"

#include "../../Engine/Engine.hpp"

class Loader : public GameStates
{
public:

	bool play() override;

private:

	void loadCarTextures1();
	void loadCarTextures2();
	void loadMapTiles();
	void loadOtherTextures();
	void loadTexturesWithName();
	void checkCarsConfigFiles();

	void drawLoadingText(const std::string &text);

	void error(const std::string &path);

	bool isError;

	Text *text;
	Text *loadText;

	// all path will be in binary file soon

	std::vector<std::string> carsName = {
		"Ambulance",
		"Audi",
		"Black_viper",
		"Car",
		"Mini_truck",
		"Police",
		"Taxi"
	};

	std::vector<std::string> carTextures1 = {
		"data/Models/Cars/carName/tire.gk",
		"data/Models/Cars/carName/doors/leftF.gk",
		"data/Models/Cars/carName/doors/rightF.gk",
		"data/Models/Cars/carName/tracesTexture/asphalt.gk",
		"data/Models/Cars/carName/tracesTexture/grass.gk"
	};

	std::vector<std::string> carTextures2 = {
		"data/Models/Cars/Ambulance/ambulance.gk",
		"data/Models/Cars/Ambulance/ambulance_shadow.gk",

		"data/Models/Cars/Audi/audi.gk",
		"data/Models/Cars/Audi/audi_shadow.gk",

		"data/Models/Cars/Black_viper/black_viper.gk",
		"data/Models/Cars/Black_viper/black_viper_shadow.gk",

		"data/Models/Cars/Car/car.gk",
		"data/Models/Cars/Car/car_shadow.gk",

		"data/Models/Cars/Mini_truck/mini_truck.gk",
		"data/Models/Cars/Mini_truck/mini_truck_shadow.gk",

		"data/Models/Cars/Police/police.gk",
		"data/Models/Cars/Police/police_shadow.gk",

		"data/Models/Cars/Taxi/taxi.gk",
		"data/Models/Cars/Taxi/taxi_shadow.gk",
	};

	std::vector<std::string> carTextures3 = {
		"data/Models/Cars/Audi/doors/rightB.gk",
		"data/Models/Cars/Audi/doors/leftB.gk",

		"data/Models/Cars/Car/doors/rightB.gk",
		"data/Models/Cars/Car/doors/leftB.gk",

		"data/Models/Cars/Police/doors/rightB.gk",
		"data/Models/Cars/Police/doors/leftB.gk",

		"data/Models/Cars/Taxi/doors/rightB.gk",
		"data/Models/Cars/Taxi/doors/leftB.gk"
	};

	std::vector<std::string> otherTextures = {
		"data/Game/keyboard.gk",
		"data/Game/MenuInGame/leftArrow.gk",
		"data/Game/MenuInGame/rightArrow.gk",
		"data/Models/Cars/Ambulance/animation/ambulance1.gk",
		"data/Models/Cars/Ambulance/animation/ambulance2.gk",
		"data/Models/Cars/Ambulance/animation/ambulance3.gk",
		"data/Models/Cars/Police/animation/police1.gk",
		"data/Models/Cars/Police/animation/police2.gk",
		"data/Models/Cars/Police/animation/police3.gk"
	};

	std::vector<std::pair<std::string, std::string>>textureWithName = {
		std::make_pair("playerMinimap", "data/Map/Minimap/player.gk"),
		std::make_pair("targetMinimap", "data/Map/Minimap/target.gk")
	};

	std::vector<std::string> mapTiles = {
		"data/Map/Tileset/asphalt.gk",
		"data/Map/Tileset/asphalt_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_BL.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_BL_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_BR.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_BR_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_TL.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_TL_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_TR.gk",
		"data/Map/Tileset/asphalt_grass_corner_in_TR_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_BL.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_BL_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_BR.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_BR_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_TL.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_TL_G.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_TR.gk",
		"data/Map/Tileset/asphalt_grass_corner_out_TR_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_BOTT.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_BOTT_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_LEFT.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_LEFT_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_RIGHT.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_RIGHT_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_TOP.gk",
		"data/Map/Tileset/asphalt_grass_hor_border_TOP_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_BL.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_BL_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_BR.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_BR_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_TL.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_TL_G.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_TR.gk",
		"data/Map/Tileset/asphalt_grass_hor_pedlanes_TR_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_BL.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_BL_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_BR.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_BR_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_TL.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_TL_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_TR.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_hor_border_TR_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_BL.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_BL_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_BR.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_BR_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_TL.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_TL_G.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_TR.gk",
		"data/Map/Tileset/asphalt_grass_pvmt_vert_border_TR_G.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_BL.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_BL_G.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_BR.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_BR_G.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_TL.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_TL_G.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_TR.gk",
		"data/Map/Tileset/asphalt_grass_vert_pedlanes_TR_G.gk",
		"data/Map/Tileset/asphalt_hor_lane_LEFT.gk",
		"data/Map/Tileset/asphalt_hor_lane_RIGHT.gk",
		"data/Map/Tileset/asphalt_hor_pedlanes.gk",
		"data/Map/Tileset/asphalt_hor_pedlanes_LEFT.gk",
		"data/Map/Tileset/asphalt_hor_pedlanes_RIGHT.gk",
		"data/Map/Tileset/asphalt_manhole.gk",
		"data/Map/Tileset/asphalt_pavement_corner_in_BL.gk",
		"data/Map/Tileset/asphalt_pavement_corner_in_BR.gk",
		"data/Map/Tileset/asphalt_pavement_corner_in_TL.gk",
		"data/Map/Tileset/asphalt_pavement_corner_in_TR.gk",
		"data/Map/Tileset/asphalt_pavement_corner_out_BL.gk",
		"data/Map/Tileset/asphalt_pavement_corner_out_BR.gk",
		"data/Map/Tileset/asphalt_pavement_corner_out_TL.gk",
		"data/Map/Tileset/asphalt_pavement_corner_out_TR.gk",
		"data/Map/Tileset/asphalt_pavement_hor_border_BOTT.gk",
		"data/Map/Tileset/asphalt_pavement_hor_border_pedlanes_BOTT.gk",
		"data/Map/Tileset/asphalt_pavement_hor_border_pedlanes_TL.gk",
		"data/Map/Tileset/asphalt_pavement_hor_border_pedlanes_TOP.gk",
		"data/Map/Tileset/asphalt_pavement_hor_border_TOP.gk",
		"data/Map/Tileset/asphalt_pavement_hor_pedlanes_BL.gk",
		"data/Map/Tileset/asphalt_pavement_hor_pedlanes_BR.gk",
		"data/Map/Tileset/asphalt_pavement_hor_pedlanes_TR.gk",
		"data/Map/Tileset/asphalt_pavement_vert_border_LEFT.gk",
		"data/Map/Tileset/asphalt_pavement_vert_border_pedlanes_LEFT.gk",
		"data/Map/Tileset/asphalt_pavement_vert_border_pedlanes_RIGHT.gk",
		"data/Map/Tileset/asphalt_pavement_vert_border_RIGHT.gk",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_BL.gk",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_BR.gk",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_TL.gk",
		"data/Map/Tileset/asphalt_pavement_vert_pedlanes_TR.gk",
		"data/Map/Tileset/asphalt_vert_lane_BOTT.gk",
		"data/Map/Tileset/asphalt_vert_lane_TOP.gk",
		"data/Map/Tileset/asphalt_vert_pedlanes.gk",
		"data/Map/Tileset/asphalt_vert_pedlanes_BOTT.gk",
		"data/Map/Tileset/asphalt_vert_pedlanes_TOP.gk",
		"data/Map/Tileset/grass.gk",
		"data/Map/Tileset/grass_G.gk",
		"data/Map/Tileset/grass_pavement_corner_in_BL.gk",
		"data/Map/Tileset/grass_pavement_corner_in_BL_G.gk",
		"data/Map/Tileset/grass_pavement_corner_in_BR.gk",
		"data/Map/Tileset/grass_pavement_corner_in_BR_G.gk",
		"data/Map/Tileset/grass_pavement_corner_in_TL.gk",
		"data/Map/Tileset/grass_pavement_corner_in_TL_G.gk",
		"data/Map/Tileset/grass_pavement_corner_in_TR.gk",
		"data/Map/Tileset/grass_pavement_corner_in_TR_G.gk",
		"data/Map/Tileset/grass_pavement_corner_out_BL.gk",
		"data/Map/Tileset/grass_pavement_corner_out_BL_G.gk",
		"data/Map/Tileset/grass_pavement_corner_out_BR.gk",
		"data/Map/Tileset/grass_pavement_corner_out_BR_G.gk",
		"data/Map/Tileset/grass_pavement_corner_out_TL.gk",
		"data/Map/Tileset/grass_pavement_corner_out_TL_G.gk",
		"data/Map/Tileset/grass_pavement_corner_out_TR.gk",
		"data/Map/Tileset/grass_pavement_corner_out_TR_G.gk",
		"data/Map/Tileset/grass_pavement_hor_border_BOTT.gk",
		"data/Map/Tileset/grass_pavement_hor_border_BOTT_G.gk",
		"data/Map/Tileset/grass_pavement_hor_border_TOP.gk",
		"data/Map/Tileset/grass_pavement_hor_border_TOP_G.gk",
		"data/Map/Tileset/grass_pavement_vert_border_LEFT.gk",
		"data/Map/Tileset/grass_pavement_vert_border_LEFT_G.gk",
		"data/Map/Tileset/grass_pavement_vert_border_RIGHT.gk",
		"data/Map/Tileset/grass_pavement_vert_border_RIGHT_G.gk",
		"data/Map/Tileset/pavement.gk"
	};

	std::vector<std::string> carsConfigFiles = {
		"data/Models/Cars/CARNAME/carname.movement",
		"data/Models/Cars/CARNAME/carname.turn",
		"data/Models/Cars/CARNAME/carname.hitbox"
	};
};