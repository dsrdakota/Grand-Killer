#include "Music.hpp"

Music::Music(const std::string &musicPath)
{
	music = new sf::Music;

	music->openFromFile(musicPath);
}

Music::~Music()
{
	delete music;
}
