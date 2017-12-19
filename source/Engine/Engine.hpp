#pragma once

#include "../Game.hpp"
#include "GameStates/Menu/Play/Trailer/Trailer.hpp"

#include "GameStates/Intro/Intro.hpp"
#include "GameStates/Menu/Menu.hpp"

#include <SFML/Graphics.hpp>

class Engine
{
public:

	enum class States
	{
		Intro,
		Menu,
		Exit
	};

	~Engine();

	Engine(const Engine &) = delete;
	void operator=(const Engine &) = delete;	

	inline static Engine& Instance()
	{
		static Engine engine;
		return engine;
	}

	inline static smallerEngine* getWsk() { return Engine::Instance().wsk; }
	inline static States getState() { return Engine::Instance().state; }

	static void nextPartGame();

private:
	Engine();
	States state;
	smallerEngine *wsk;
	
	Intro intro;
	Menu menu;

protected:
	Game &game;
	sf::RenderWindow *window;
};