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

	sf::View* getView() const;
	static void updateView(IObject *player);
	static bool isOutsideView(const sf::Vector2f &position);
	static bool isOutsideView(const sf::FloatRect &box);

private:

	sf::View *view;

	float scale;

	Camera();

	const sf::FloatRect getViewRect() const;

	void setViewScale(IObject *player);

};