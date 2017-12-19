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


	// Trailer

	std::string path = "data/Trailer/Sound/";
	sf::Music *music = new sf::Music;

	if (!music->openFromFile(path + "background.wav"))
	{
		*errorCommunicate = "Can't open " + path + " background.wav";
		error = true;
		delete music;
		return;
	}
	delete music;


	path = "data/Trailer/Part1/Textures/";
	sf::Texture *texture = new sf::Texture;

	if(checkExist(path + "background.png",texture))
		return;
	if(checkExist(path + "phone.png",texture))
		return;
	if (checkExist(path + "phoneCall.png", texture))
		return;
	if (checkExist(path + "playerSite.png", texture))
		return;
	if (checkExist(path + "playerStand.png", texture))
		return;
	if (checkExist(path + "playerTakingPhone.png", texture))
		return;
	if (checkExist(path + "playerTalking.png", texture))
		return;

	path = "data/Trailer/Part2/Textures/";
	if (checkExist(path + "background.png", texture))
		return;
	if (checkExist(path + "plane.png", texture))
		return;

	path = "data/Trailer/Part3/Textures/";
	if (checkExist(path + "background.png", texture))
		return;
	if (checkExist(path + "BackL.png", texture))
		return;
	if (checkExist(path + "centerBackL.png", texture))
		return;
	if (checkExist(path + "playerSite.png", texture))
		return;
	if (checkExist(path + "taxi.png", texture))
		return;
	if (checkExist(path + "Walk/head.png", texture))
		return;
	for (int i = 0;i <= 20;++i)
	{
		if (checkExist(path + "Walk/body/" + std::to_string(i) + ".png", texture))
			return;
		if (i < 20)
			if (checkExist(path + "Walk/feet/" + std::to_string(i) + ".png", texture))
				return;
	}

	delete texture;

	path = "data/Trailer/Part1/Sound/";
	sf::SoundBuffer *sound = new sf::SoundBuffer;
	if (checkExist(path + "talk.wav", sound))
		return;
	if (checkExist(path + "phoneRing.wav", sound))
		return;

	path = "data/Trailer/Part2/Sound/";
	if (checkExist(path + "bum.wav", sound))
		return;
	if (checkExist(path + "plane.wav", sound))
		return;

	path = "data/Trailer/Part3/Sound/Car/";
	if (checkExist(path + "accelerating/1.wav",sound))
		return;
	if (checkExist(path + "stop/stop.wav", sound))
		return;
	if (checkExist(path + "suppressing/1.wav", sound))
		return;

	delete sound;
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

