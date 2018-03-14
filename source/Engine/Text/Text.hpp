#pragma once

#include <SFML/Graphics.hpp>

class Text
{
public:

	sf::Font *font;
	sf::Text *text;

	Text(const sf::Color &color, const unsigned &Size, const std::string &String = "", const std::string &fontName = "arial");
	~Text();
};