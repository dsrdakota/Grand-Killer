#pragma once

#include <SFML/Graphics.hpp>

#include "States/StatesManager.hpp"

class Game
{
public:

	Game(const Game &) = delete;
	void operator=(const Game &) = delete;
	
	inline static Game& Instance()
	{
		static Game game;
		return game;
	}

	enum class status
	{
		Initializing,
		Error,
		Running,
		Paused,
		CleaningUp
	};

	inline status getStatus() const { return m_status; }

	inline sf::RenderWindow* getWindow() { return window; }

	inline void close() { m_status = status::CleaningUp; }

	void run();

	void events();
	static int* getScrollValue();

private:
	
	sf::RenderWindow *window;

	GameStatesManager *states;

	status m_status;
	int scrollValue;
	sf::Image icona;

	Game();
	void setIco();
	bool checkFilesToLoadingScreen();
	bool checkExistFont(const std::string &pathToFont, const std::string &fontName);
};