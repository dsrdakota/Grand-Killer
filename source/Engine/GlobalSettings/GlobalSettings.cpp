#include "GlobalSettings.hpp"

GlobalSettings::GlobalSettings()
{
}

GlobalSettings::~GlobalSettings()
{
}

unsigned & GlobalSettings::getWidth()
{
	return Instance().width;
}

unsigned & GlobalSettings::getHeight()
{
	return Instance().height;
}

unsigned & GlobalSettings::getColors()
{
	return Instance().colors;
}

unsigned & GlobalSettings::getFps()
{
	return Instance().fps;
}

sf::ContextSettings & GlobalSettings::getSettings()
{
	return Instance().settings;
}

sf::Uint32 & GlobalSettings::getWindowMode()
{
	return Instance().windowMode;
}

bool & GlobalSettings::getVerticalSync()
{
	return Instance().verticalSync;
}
