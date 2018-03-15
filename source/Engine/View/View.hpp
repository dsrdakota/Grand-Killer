#pragma once

#include <SFML/Graphics.hpp>

#include "../../IObject/IObject.hpp"
#include "../../Game.hpp"

class View
{
public:

	~View();

	View(const View &) = delete;
	void operator=(const View &) = delete;

	inline static View& Instance()
	{
		static View view;
		return view;
	}

	static sf::View* getView();
	static sf::Vector2u getSize();
	static void updateView(IObject *player);
	static bool isOutSideView(const sf::Vector2f &position);
	static bool isOutSideView(const sf::FloatRect &box);
	static sf::Vector2f getUpLeftCornerPosOfCurrentView();

private:

	sf::View *view;

	View();
	sf::FloatRect getViewBox();
	void setView(const sf::Vector2f & center);
};