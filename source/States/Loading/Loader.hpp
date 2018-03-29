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
	void loadCarDoors();
	void loadCarTires();
	void loadMapTiles();
	void loadOtherTextures();
	void loadTexturesWithName();
	void checkCarsConfigFiles();
	void checkTxtFiles();

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
		"Dodge",
		"Mini_truck",
		"Police",
		"Taxi"
	};

	std::vector<std::string> carTextures1 = {
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

		"data/Models/Cars/Dodge/dodge.gk",
		"data/Models/Cars/Dodge/dodge_shadow.gk",

		"data/Models/Cars/Mini_truck/mini_truck.gk",
		"data/Models/Cars/Mini_truck/mini_truck_shadow.gk",

		"data/Models/Cars/Police/police.gk",
		"data/Models/Cars/Police/police_shadow.gk",

		"data/Models/Cars/Taxi/taxi.gk",
		"data/Models/Cars/Taxi/taxi_shadow.gk",
	};

	std::vector<std::string> carDoors = {
		"data/Models/Cars/carName/doors/leftF.gk",
		"data/Models/Cars/carName/doors/rightF.gk",
	};

	std::vector<std::string> carTires = {
		"data/Models/Cars/carName/tire/",
	};

	std::vector<std::string> otherTextures = {
		"data/Game/keyboard.gk",
		"data/Game/Menu/leftArrow.gk",
		"data/Game/Menu/rightArrow.gk",
		"data/Models/Cars/Ambulance/animation/ambulance1.gk",
		"data/Models/Cars/Ambulance/animation/ambulance2.gk",
		"data/Models/Cars/Ambulance/animation/ambulance3.gk",
		"data/Models/Cars/Police/animation/police1.gk",
		"data/Models/Cars/Police/animation/police2.gk",
		"data/Models/Cars/Police/animation/police3.gk"
	};

	std::vector<std::pair<std::string, std::string>>textureWithName = {
		std::make_pair("playerMinimap", "data/Map/Minimap/player.gk"),
		std::make_pair("targetMinimap", "data/Map/Minimap/target.gk"),
		std::make_pair("Audi_rightB", "data/Models/Cars/Audi/doors/rightB.gk"),
		std::make_pair("Audi_leftB", "data/Models/Cars/Audi/doors/leftB.gk"),
		std::make_pair("Dodge_rightB", "data/Models/Cars/Dodge/doors/rightB.gk"),
		std::make_pair("Dodge_leftB", "data/Models/Cars/Dodge/doors/leftB.gk"),
		std::make_pair("Police_rightB", "data/Models/Cars/Police/doors/rightB.gk"),
		std::make_pair("Police_leftB", "data/Models/Cars/Police/doors/leftB.gk"),
		std::make_pair("Taxi_rightB", "data/Models/Cars/Taxi/doors/rightB.gk"),
		std::make_pair("Taxi_leftB", "data/Models/Cars/Taxi/doors/leftB.gk"),
	};

	std::vector<std::string> carsConfigFiles = {
		"data/Models/Cars/CARNAME/carname.movement",
		"data/Models/Cars/CARNAME/carname.turn",
		"data/Models/Cars/CARNAME/carname.hitbox"
	};

	std::vector<std::string> txtFiles = {
		"data/Map/Tileset/Tiles.txt",
		"data/Map/Tileset/GPS.txt",
	};
};