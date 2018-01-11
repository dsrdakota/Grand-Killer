#include "Game.hpp"
#include "Framework/Settings.hpp"
#include "Manager/Text.hpp"
#include "Framework/Error.hpp"
#include "Engine/GameStates/Menu/Play/Trailer/Trailer.hpp"
#include "Manager/Texture.hpp"
#include "Manager/Sound.hpp"

#include "Engine/Engine.hpp"

#define Double 1.0
#define Bool true

Game::Game() : m_status(status::Initializing)
{
	Settings *config = new Settings;
	m_status = (Game::status)config->parseFile();
	if (m_status != Game::status::Error)
	{
		unsigned width = 0, height = 0, colors = 32;
		width = (unsigned)config->giveMeValue("GENERAL", "Width", Double);
		height = (unsigned)config->giveMeValue("GENERAL", "Height", Double);
		colors = (unsigned)config->giveMeValue("GENERAL", "Colors", Double);

		fps = (unsigned)config->giveMeValue("GENERAL", "Fps", Double);

		sf::ContextSettings settings = (sf::ContextSettings)(unsigned)config->giveMeValue("GENERAL", "AntialiasingLevel", Double);

		sf::Uint32 windowMode = (sf::Uint32)config->giveMeValue("GENERAL", "WindowMode", Double);

		if (windowMode)
			windowMode = sf::Style::Default;
		else
			windowMode = sf::Style::Fullscreen;

		window = new sf::RenderWindow(sf::VideoMode(width, height, colors), "Grand Killer", windowMode, settings);
		window->setFramerateLimit(fps);
		window->setVerticalSyncEnabled(true);
		window->setMouseCursorVisible(false);

	}
	else
		window = new sf::RenderWindow(sf::VideoMode(300, 100, 32), "Grand Killer",sf::Style::Default);

	delete config;	

	//setIco();
}

void Game::setIco()
{
	icona.loadFromFile("Icona2.png");
	window->setIcon(icona.getSize().x,icona.getSize().y, icona.getPixelsPtr());
}

Game::~Game()
{
	if (!Error::Instance().getErrorBool())
	{
		if (window->isOpen())
			window->close();
		delete window;
	}
}

void Game::events(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q))
			m_status = status::CleaningUp;

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta < 0)
				scrollValue = -1;
			else if (event.mouseWheelScroll.delta > 0)
				scrollValue = 1;
		}
		else
			scrollValue = 0;
	}
}

void Game::loadingScreen()
{
	auto &game = Game::Instance();
	auto window = game.getWindow();

	window->setView(window->getDefaultView());

	Text loading(sf::Color::White, 50, "Loading...");

	loading.text->setPosition(window->getSize().x / 2 - loading.text->getGlobalBounds().width / 2, window->getSize().y / 2 - loading.text->getGlobalBounds().height / 2);

	window->clear(sf::Color::Black);
	window->draw(*loading.text);
	window->display();
}

int Game::getScrollValue()
{
	return Instance().scrollValue;
}

void Game::run()
{
	m_status = status::Running;

	while (m_status != status::CleaningUp && Engine::getState() != Engine::States::Exit)
	{
		if(Engine::getWsk() != nullptr)
			Engine::getWsk()->play();

		Engine::nextPartGame();
	}
}