#include "Error.hpp"
#include "../Game.hpp"
#include "../Manager/Text.hpp"

#include <SFML/Audio.hpp>

#include <fstream>

Error::Error()
{
	error = false;
	errorCommunicate = new std::string;
}

Error::~Error()
{
	delete errorCommunicate;
}

void Error::checkAllFiles()
{
	sf::Font *font = new sf::Font;
	if (!font->loadFromFile("data/Font/arial.ttf"))
	{
		*errorCommunicate = "Can't open data/Font/arial.ttf";
		error = true;
		delete font;
		return;
	}
	if (!font->loadFromFile("data/Font/curlz.ttf"))
	{
		*errorCommunicate = "Can't open data/Font/curlz.ttf";
		error = true;
		delete font;
		return;
	}
	if (!font->loadFromFile("data/Font/italic.ttf"))
	{
		*errorCommunicate = "Can't open data/Font/italic.ttf";
		error = true;
		delete font;
		return;
	}
	delete font;

	std::ifstream *file = new std::ifstream("game.cfg");
	if (!file->good())
	{
		*errorCommunicate = "Can't open game.cfg";
		error = true;
		delete file;
		return;
	}
	delete file;



	// Intro



	// Menu



	// Play



	// Trailer



}

template <class T>
bool Error::checkExist(const std::string &path,T *buffer)
{
	if (!buffer->loadFromFile(path))
	{
		*errorCommunicate = "Can't open " + path;
		error = true;
		delete buffer;
		return true;
	}
	return false;
}

template bool Error::checkExist(const std::string &, sf::Texture *);
template bool Error::checkExist(const std::string &, sf::SoundBuffer *);

void Error::showCommunicate()
{
	auto &game = Game::Instance();
	auto window = game.getWindow();
	delete window;

	Text communicate(sf::Color::Red, 20, *Error::Instance().errorCommunicate);

	unsigned windowWidth;
	if ((unsigned)communicate.text->getGlobalBounds().width + 10 < 300)
		windowWidth = 300;
	else
		windowWidth = (unsigned)communicate.text->getGlobalBounds().width + 10;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, 100, 32), "Grand Killer - Error !", sf::Style::Default);

	while (game.getStatus() != Game::status::CleaningUp)
	{
		game.events(*window);

		window->clear(sf::Color(255, 255, 255));
		window->draw(*communicate.text);
		window->display();
	}
	window->close();
	delete window;
}

