#pragma once

#include <SFML/Graphics.hpp>

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

	static sf::Vector2u getSize();
	static bool isOutSideView(const sf::Vector2f &position);
	static bool isOutSideView(const sf::FloatRect &box);
	static sf::Vector2f getUpLeftCornerPosOfCurrentView();

private:

	sf::View *view;
	sf::Vector2u size;

	View();
	sf::FloatRect getViewBox();
};