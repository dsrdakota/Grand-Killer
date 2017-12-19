#pragma once

#include <SFML/Audio.hpp>

#include <string>

class Music
{
public:
	sf::Music *music;
	
	Music(const std::string &musicPath);

	~Music();
};