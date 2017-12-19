#include "Text.hpp"

Text::Text(const sf::Color & color, const unsigned & Size, const std::string & String, const std::string &fontPath)
{
	font = new sf::Font;
	text = new sf::Text;

	if (!font->loadFromFile(fontPath))
		return;

	text->setFont(*font);
	text->setCharacterSize(Size);
	text->setFillColor(sf::Color(color));
	text->setString(String);
}

Text::~Text()
{
	delete font;
	delete text;
}