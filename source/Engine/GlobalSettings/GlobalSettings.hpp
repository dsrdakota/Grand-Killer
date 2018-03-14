#pragma once

#include <SFML/Graphics.hpp>

class GlobalSettings
{
public:

	~GlobalSettings();

	GlobalSettings(const GlobalSettings &) = delete;
	void operator=(const GlobalSettings &) = delete;

	inline static GlobalSettings& Instance()
	{
		static GlobalSettings settings;
		return settings;
	}

	inline static unsigned &getWidth() { return Instance().width; }
	inline static unsigned &getHeight() { return Instance().height; }
	inline static unsigned &getColors() { return Instance().colors; }
	inline static unsigned &getFps() { return Instance().fps; }
	inline static sf::ContextSettings &getSettings() { return Instance().settings; }
	inline static sf::Uint32 &getWindowMode() { return Instance().windowMode; }
	inline static bool &getVerticalSync() { return Instance().verticalSync; }

private:

	unsigned width, height, colors, fps;
	sf::ContextSettings settings;
	sf::Uint32 windowMode;
	bool verticalSync;

	GlobalSettings();
};