#pragma once

#include <SFML/Graphics.hpp>
#include "../../../../../Manager/Music.hpp"

class TrailerStates
{
public:

	TrailerStates();
	~TrailerStates();

	unsigned frame;
	sf::RectangleShape *dark;
	sf::Sprite *backgroundImg;

	virtual void play(sf::RenderWindow *window, const sf::Time &time, Music &background, bool &changePart) = 0;

	unsigned transparency;

	inline void boostTransparencyBackground(const unsigned &value = 2)
	{
		if (transparency + value > 255)
			transparency = 255;
		else
			transparency += value;
	}

	inline void reduceTransparencyBackground(const unsigned &value = 2)
	{
		if (transparency < value)
			transparency = 0;
		else
			transparency -= value;
	}

	enum class statePart
	{
		Begin,
		First,
		Second,
		Third,
		End
	};
};