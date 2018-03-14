#include "Text.hpp"
#include "../Font/Font.hpp"

Text::Text(const sf::Color & color, const unsigned & Size, const std::string & String, const std::string &fontName)
{
	font = new sf::Font;
	text = new sf::Text;

	text->setFont(*FontManager::getFont(fontName));
	text->setCharacterSize(Size);
	text->setFillColor(sf::Color(color));
	text->setString(String);
}

Text::~Text()
{
	delete font;
	delete text;
}