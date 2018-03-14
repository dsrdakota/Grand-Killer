#pragma once

#include "SFML/Graphics.hpp"

#include <unordered_map>

class FontManager
{
public:

	FontManager(const FontManager &) = delete;
	void operator=(const FontManager &) = delete;

	static void addFont(const std::string &name, sf::Font* font);
	static sf::Font* getFont(const std::string &name);

private:

	std::unordered_map<std::string, sf::Font*> fonts;

	FontManager() { ; }

	inline static FontManager& Instance()
	{
		static FontManager font;
		return font;
	}
};