#include "Engine.hpp"

#include "GlobalSettings/GlobalSettings.hpp"

void Engine::init()
{
	Config *config = new Config;
	int status = config->parseFile();

	if (status == 1)
		getValuesFromFile(config);
	else
		setDefault();

	saveSettings();

	window = new sf::RenderWindow(sf::VideoMode(width, height, colors), "Grand Killer", windowMode, settings);
	window->setFramerateLimit(fps);
	window->setVerticalSyncEnabled(verticalSync);
	window->setMouseCursorVisible(false);

	delete config;
}

void Engine::shutDown()
{
	delete window;
}

void Engine::getValuesFromFile(Config *cfgFile)
{
	width = (unsigned)cfgFile->giveMeValue("GENERAL", "Width");
	height = (unsigned)cfgFile->giveMeValue("GENERAL", "Height");
	colors = (unsigned)cfgFile->giveMeValue("GENERAL", "Colors");
	fps = (unsigned)cfgFile->giveMeValue("GENERAL", "Fps");
	settings = (sf::ContextSettings)(unsigned)cfgFile->giveMeValue("GENERAL", "AntialiasingLevel");
	windowMode = (sf::Uint32)cfgFile->giveMeValue("GENERAL", "WindowMode");
	verticalSync = cfgFile->giveMeValue("GENERAL", "VerticalSync");

	if (windowMode)
		windowMode = sf::Style::Default;
	else
		windowMode = sf::Style::Fullscreen;

	if (width < 1 || height < 1 || fps < 1)
		setDefault();
}

void Engine::setDefault()
{
	width = 1366;
	height = 768;
	colors = 32;
	fps = 60;
	settings = static_cast<sf::ContextSettings>(8);
	verticalSync = true;
	windowMode = sf::Style::Fullscreen;
}

void Engine::saveSettings()
{
	GlobalSettings::getWidth() = width;
	GlobalSettings::getHeight() = height;
	GlobalSettings::getFps() = fps;
	GlobalSettings::getColors() = colors;
	GlobalSettings::getSettings() = settings;
	GlobalSettings::getVerticalSync() = verticalSync;
	GlobalSettings::getWindowMode() = windowMode;
}
