#include "Game.hpp"
#include "Engine/Engine.hpp"

#if defined(_WIN32) || defined(WIN32) 

#define OS_Windows
#include <Windows.h>

#endif

Game::Game() : m_status(status::Initializing), window(Engine::Instance().window)
{
	//setIco();
}

void Game::setIco()
{
	icona.loadFromFile("Icona.png");
	window->setIcon(icona.getSize().x,icona.getSize().y, icona.getPixelsPtr());
}

void Game::events()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q))
			m_status = status::CleaningUp;

		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta < 0)
				scrollValue = -1;
			else if (event.mouseWheel.delta > 0)
				scrollValue = 1;
		}
	}
}

int* Game::getScrollValue()
{
	return &Instance().scrollValue;
}

void Game::run()
{
	m_status = status::Running;

	if (!checkFilesToLoadingScreen())
		return;

	states = new GameStatesManager;
	states->runState();
}

bool Game::checkFilesToLoadingScreen()
{
	if (!checkExistFont("data/Font/arial.ttf", "arial"))
		return false;
	
	if (!checkExistFont("data/Font/curlz.ttf", "curlz"))
		return false;

	if (!checkExistFont("data/Font/italic.ttf", "italic"))
		return false;

	// load textures

	return true;
}

bool Game::checkExistFont(const std::string & pathToFont, const std::string &fontName)
{
	sf::Font *font = new sf::Font;
	std::string communicate;
	if (!font->loadFromFile(pathToFont))
	{
		communicate = "Can't open " + pathToFont;

#ifdef OS_Windows
		MessageBox(NULL, communicate.c_str(), "Grand Killer - Error !", MB_ICONERROR | MB_OK);
#endif

		delete font;
		return false;
	}
	FontManager::addFont(fontName, font);
	return true;
}