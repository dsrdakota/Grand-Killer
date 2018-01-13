#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Settings.hpp"

class Game
{
public:
	unsigned fps;
	~Game();

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
	void events(sf::RenderWindow &window = *Game::Instance().getWindow());

	static void loadingScreen();
	static int* getScrollValue();

private:
	
	Game();
	status m_status;

	int scrollValue;

	sf::Image icona;
	void setIco();

protected:
	sf::RenderWindow *window;
};