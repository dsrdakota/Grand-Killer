#include "Font.hpp"

void FontManager::addFont(const std::string & name, sf::Font * font)
{
	Instance().fonts[name] = font;
}

sf::Font * FontManager::getFont(const std::string & name)
{
	if (Instance().fonts.find(name) == Instance().fonts.end())
		return nullptr;
	return Instance().fonts[name];
}
