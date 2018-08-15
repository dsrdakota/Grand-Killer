#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.hpp"

#include "Button/Button.hpp"
#include "Config/Config.hpp"
#include "Font/Font.hpp"
#include "Keyboard/Keyboard.hpp"
#include "Music/Music.hpp"
#include "Rendering/Painter.hpp"
#include "Sound/Sound.hpp"
#include "Textures/Texture.hpp"
#include "Camera/Camera.hpp"
#include "Time/Time.hpp"
#include "GlobalSettings/GlobalSettings.hpp"
#include "GlobalSettings/GlobalSteerage.hpp"
#include "Config/CarConfig.hpp"
#include "World/World.hpp"

class Engine
{
public:

	~Engine() { ; }

	Engine(const Engine &) = delete;
	void operator=(const Engine &) = delete;

	inline static Engine& Instance()
	{
		static Engine engine;
		return engine;
	}

	void init();
	void shutDown();

private:

	sf::RenderWindow *window;

	unsigned width, height, colors, fps;
	sf::ContextSettings settings;
	sf::Uint32 windowMode;
	bool verticalSync;

	Engine() { ; }

	void getValuesFromFile(Config *cfgFile);
	void setDefault();
	void saveSettings();

	friend class Game;
};