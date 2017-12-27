#pragma once

#include <SFML/Graphics.hpp>

class Sign
{
public:

	Sign(const sf::Vector2f &startPos = sf::Vector2f(0,0), const float &rotation = 0);
	~Sign();

	void setPosition(const sf::Vector2f &startPos, const float &rotation = 0);

	sf::Sprite *getSignSprite();
	sf::CircleShape *getSignHitbox();
	int getDrawState();

private:

	enum class drawState
	{
		Under = -1,
		On = 1
	};

	sf::Sprite *sign;
	sf::CircleShape *hitbox;
	drawState state;

	sf::Vector2f startPos;
	float startRotation;
};