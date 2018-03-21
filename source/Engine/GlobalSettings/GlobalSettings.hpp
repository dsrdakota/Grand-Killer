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

	static unsigned &getWidth();
	static unsigned &getHeight();
	static unsigned &getColors();
	static unsigned &getFps();
	static sf::ContextSettings &getSettings();
	static sf::Uint32 &getWindowMode();
	static bool &getVerticalSync();

private:

	unsigned width, height, colors, fps;
	sf::ContextSettings settings;
	sf::Uint32 windowMode;
	bool verticalSync;

	GlobalSettings();
};