#pragma once

#include <SFML/Graphics.hpp>

#include "../../IObject/IObject.hpp"
#include "../../Game.hpp"

class Camera
{
public:

	~Camera();

	Camera(const Camera &) = delete;
	void operator=(const Camera &) = delete;

	inline static Camera& Instance()
	{
		static Camera view;
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

	Camera();
	sf::FloatRect getViewBox();
	void setView(const sf::Vector2f & center);
};